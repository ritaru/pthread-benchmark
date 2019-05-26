#include "performanceTimer.hpp"

performanceTimer::performanceTimer() {
	
}

performanceTimer::~performanceTimer() {

}

void performanceTimer::start() {
	if (!QueryPerformanceFrequency(&begin))
		throw - 1;
	_cpuFreq = (double)begin.QuadPart / 1000.0;
	QueryPerformanceCounter(&begin);
}

double performanceTimer::getTime() {	
	QueryPerformanceCounter(&end);
	return (double)(end.QuadPart - begin.QuadPart) / _cpuFreq;
}
