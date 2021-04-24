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
	if (this->completedOperations == this->requiredOperations) // считаем кол-во завершенных потоков, чтобы разблокировать кнопку запуска
	{
		this->isInProgress = false;
		this->completedOperations = 0;
		ui->label->setText("Select the number of parallel operations:");
	}
}

void MainWindow::on_pushButton_clicked() // если нажата кнопка
{
	if (this->isInProgress == true)
	{
		QMessageBox::warning(this, "Warning", "In progress"); // блокируем кнопку запуска, если процесс уже идет
		return;
	}

	this->requiredOperations = ui->spinBox->value();
	if (this->requiredOperations > 0)
	{
		this->isInProgress = true;
		ui->label->setText("In progress");

		if (this->requiredOperations > 10)
			QMessageBox::warning(this, "Warning", "The computer can be very slow");

		MyModel* model = new MyModel(); // создаем модель для таблицы
		QThreadPool::globalInstance()->setMaxThreadCount(this->requiredOperations);
		for (size_t i = 0; i < this->requiredOperations; ++i)
		{
			SomeSeriousFunc* ssf = new SomeSeriousFunc();
			ssf->setAutoDelete(true);
			QStandardItem* row = new QStandardItem("Trying to start...");
			model->setItem(i, row); // добавляем в модель строку
			// подключаем сигналы потоков к слотам mainwindow
			QObject::connect((QObject*)ssf, SIGNAL(newStateNotify(const unsigned long long&, const QString&)), model, SLOT(setText(const unsigned long long&, const QString&)));
			QObject::connect((QObject*)ssf, SIGNAL(operationIsDoneNotify()), this, SLOT(operationIsDone()));
			// запускаем поток
			QThreadPool::globalInstance()->start(ssf);
		}
		// заполняем таблицу и настраиваем ее
		model->setHeaderData(0, Qt::Horizontal, "Threads");
		delete ui->tableView->selectionModel(); // удаляем старую модель
		ui->tableView->setModel(model);
		model->setParent(ui->tableView); // привязываем модель к таблице, чтобы в дальнейшем удалилась сама
		ui->tableView->setColumnWidth(0, ui->tableView->width());
	}
}
