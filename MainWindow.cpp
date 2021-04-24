#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::operationIsDone()
{
	++this->completedOperations;
	if (this->completedOperations == this->requiredOperations)
	{
		this->isInProgress = false;
		this->completedOperations = 0;
		ui->label->setText("Select the number of parallel operations:");
	}
}

void MainWindow::on_pushButton_clicked()
{
	if (this->isInProgress == true)
	{
		QMessageBox::warning(this, "Warning", "In progress");
	}
	else
	{
		this->requiredOperations = ui->spinBox->value();
		if (this->requiredOperations > 0)
		{
			this->isInProgress = true;
			ui->label->setText("In progress");
		}
		if (this->requiredOperations > 10)
			QMessageBox::warning(this, "Warning", "The computer can be very slow");
		MyModel* model = new MyModel();
		QThreadPool::globalInstance()->setMaxThreadCount(this->requiredOperations);
		for (size_t i = 0; i < this->requiredOperations; ++i)
		{
			SomeSeriousFunc* ssf = new SomeSeriousFunc();
			QStandardItem* row = new QStandardItem("Trying to start...");
			model->setItem(i, 0, row);
			QObject::connect((QObject*)ssf, SIGNAL(newStateNotify(const unsigned long long&, const QString&)), model, SLOT(setText(const unsigned long long&, const QString&)));
			QObject::connect((QObject*)ssf, SIGNAL(operationIsDoneNotify()), this, SLOT(operationIsDone()));
			QThreadPool::globalInstance()->start(ssf);
		}
		model->setHeaderData(0, Qt::Horizontal, "Threads");
		ui->tableView->setModel(model);
		ui->tableView->setColumnWidth(0, ui->tableView->width());
	}
}
