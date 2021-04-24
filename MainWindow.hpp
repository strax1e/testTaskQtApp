#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "SomeSeriousFunc.hpp"
#include "MyModel.hpp"
#include <QMainWindow>
#include <QThreadPool>
#include <QStandardItem>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pushButton_clicked();
	void operationIsDone();

private:
	Ui::MainWindow *ui;
	bool isInProgress = false;
	size_t completedOperations = 0;
	size_t requiredOperations = 0;

};
#endif // MAINWINDOW_HPP
