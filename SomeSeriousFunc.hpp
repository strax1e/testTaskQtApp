#ifndef SOMESERIOUSFUNC_HPP
#define SOMESERIOUSFUNC_HPP

#include <QMutexLocker>
#include <QRunnable>
#include <QObject>
#include <string>

class SomeSeriousFunc : public QObject, public QRunnable
{
	Q_OBJECT
public:
	SomeSeriousFunc() = default;
	void run() override;

private:
	static QMutex mutex;
	static size_t counterOfCalls;

signals:
	void newStateNotify(const unsigned long long& index, const QString&);
	void operationIsDoneNotify();
};

#endif // SOMESERIOUSFUNC_HPP
