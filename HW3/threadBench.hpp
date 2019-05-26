#define HAVE_STRUCT_TIMESPEC 1

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "pthread.h"
#include "performanceTimer.hpp"

class threadBench {
private:
	// Size of array.
	unsigned long long _testSize;
	double *S, *A, *B;

	// pthread Array.
	pthread_t *pthread;
	// pthread ID Array.
	int *threadId;
	// threadWorkSize = _testSize / _threadNum
	unsigned long long threadWorkSize;
	int _threadNum;
	struct threadParam {
		double *_S, *_A, *_B;
		unsigned long long startIndex;
	};
	threadParam *param;

	void threadFunction(threadParam *param);

	// The pthread library cannot handle class method pointer directly, so I made a simple wrapper function for it.
	static void *threadFunctionWrapper(void *C) {
		threadBench *temp = static_cast<threadBench *>(C);
		temp->threadFunction(((threadBench *)C)->param);
		return NULL;
	}

public:
	// threadNum is default by 0, not using pthread.
	threadBench(unsigned long long testSize, int threadNum = 0);
	~threadBench();
	void run();
	double sumResult();
	int benchmark();
};