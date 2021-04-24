#ifndef SOMESERIOUSFUNC_HPP
#define SOMESERIOUSFUNC_HPP

#include <QMutexLocker>
#include <QRunnable>
#include <QObject>
#include <string>

// класс с "ресурсоёмкой" функцией
class SomeSeriousFunc : public QObject, public QRunnable
{
	Q_OBJECT
public:
	SomeSeriousFunc() = default;
	void run() override;

private:
	static QMutex mutex;
	static size_t counterOfCalls; // счетчик кол-ва запущенных потоков с этой функцией

signals:
	void newStateNotify(const unsigned long long& index, const QString&); // сигнал для обновления состояния в таблице
	void operationIsDoneNotify(); // сигнал завершения работы
};

#endif // SOMESERIOUSFUNC_HPP
