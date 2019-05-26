// Simple wrapper class for QueryPerformanceCounter / QueryPerformanceFrequency

#pragma once

// There is an error when Windows.h is added, so the if-endif clause is a workaround for that.

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#include <Windows.h>

class performanceTimer {
private:
	double _cpuFreq;
	LARGE_INTEGER begin;
	LARGE_INTEGER end;
public:
	performanceTimer();
	~performanceTimer();

	void start();

	// Returns current CPU tick in ms using high precision timer
	double getTime();
};