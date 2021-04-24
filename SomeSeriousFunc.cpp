#include "SomeSeriousFunc.hpp"

QMutex SomeSeriousFunc::mutex;
size_t SomeSeriousFunc::counterOfCalls = -1;

void SomeSeriousFunc::run()
{
	const size_t myIndex = ++SomeSeriousFunc::counterOfCalls;
	const size_t N = 100000000;
	for(size_t i = 0; i <= N; ++i)
	{
		if (i % 1000 == 0)
		{
			size_t progress = (double(i) / N) * 100;
			QMutexLocker locker(&SomeSeriousFunc::mutex);
			emit newStateNotify(myIndex, QString::fromStdString(std::to_string(progress) + "% (" + std::to_string(i) + " of " + std::to_string(N) + ")"));
		}
	}
	--SomeSeriousFunc::counterOfCalls;
	emit operationIsDoneNotify();
}
