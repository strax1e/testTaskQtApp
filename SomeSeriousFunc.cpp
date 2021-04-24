#include "SomeSeriousFunc.hpp"

QMutex SomeSeriousFunc::mutex;
size_t SomeSeriousFunc::counterOfCalls = -1;

void SomeSeriousFunc::run()
{
	const size_t myIndex = ++SomeSeriousFunc::counterOfCalls; // записываемся в счетчик вызовов
	const size_t N = 100000000;
	for(size_t i = 0; i <= N; ++i)
	{
		if (i % 1000 == 0)
		{
			size_t progress = (double(i) / N) * 100;
			QMutexLocker locker(&SomeSeriousFunc::mutex);
			emit newStateNotify(myIndex, QString("%0% (%1 of %2)").arg(progress).arg(i).arg(N)); // возбуждаем сигнал о том, что пора менять запись в таблице
		}
	}
	--SomeSeriousFunc::counterOfCalls;
	emit operationIsDoneNotify(); // возбуждаем сигнал о том, что поток закончил свою работу
}
