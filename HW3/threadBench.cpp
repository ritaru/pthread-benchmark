#include "threadBench.hpp"

using namespace std;

threadBench::threadBench(unsigned long long testSize, int threadNum) {
	// Save size of test to class member variable
	_testSize = testSize;
	_threadNum = threadNum;

	// Allocate space for the test
	S = (double *)(malloc(sizeof(double) * _testSize)),
	A = (double *)(malloc(sizeof(double) * _testSize)),
	B = (double *)(malloc(sizeof(double) * _testSize));
	
	// Initialize arrays
	for (int i = 0; i < _testSize; i++) {
		A[i] = i + 1;
		B[i] = i + 2;
		S[i] = 0;
	}

	// if pthread is used
	if (threadNum) {
		// Create array of pthread table
		pthread = new pthread_t[threadNum];
		// Also calculate the work size of each thread and make array of thread ID from it
		threadWorkSize = _testSize / threadNum;
		threadId = new int[threadWorkSize];
		// Finally create a parameter for the thread function
		param = new threadParam{ S, A, B, 0 };
	}
		
}

threadBench::~threadBench() {
	// Free all dynamically allocated memory
	delete(S);
	delete(A);
	delete(B);
}

void threadBench::threadFunction(threadParam *param) {
	double *S = param->_S,
		   *A = param->_A,
		   *B = param->_B;
	unsigned long long startIndex = param->startIndex++ * threadWorkSize;
	for (unsigned long long i = startIndex; i < startIndex + threadWorkSize; i++)
		S[i] = log(A[i]) + log(B[i]);
}

void threadBench::run() {
	// Not using pthread library
	if (!_threadNum) {
		for (int i = 0; i < _testSize; i++)
			S[i] = log(A[i]) + log(B[i]);

		// Using pthread
	} else {
		for (int i = 0; i < _threadNum; i++)
			threadId[i] = pthread_create(&pthread[i], NULL, &threadFunctionWrapper, (void *)this);

		for (int i = 0; i < _threadNum; i++)
			pthread_join(pthread[i], NULL);
	}
}

double threadBench::sumResult() {
	double sum = 0;

	for (int i = 0; i < _testSize; i++)
		sum += S[i];

	return sum;
}

int threadBench::benchmark() {
	double result, duration;
	performanceTimer *simpleTimer;
	
	try {
		simpleTimer = new performanceTimer;
	} catch (int res) {
		return res;
	}

	simpleTimer->start();
	run();
	duration = simpleTimer->getTime();
	delete(simpleTimer);
	
	result = sumResult();

	cout.setf(ios_base::fixed, ios_base::floatfield);
	
	if (!_threadNum)
		cout << "Result (without pthread): " << result << endl;
	else
		cout << "Result (" << _threadNum << " threads): " << result << endl;

	cout << "Elapsed time: " << duration << "ms" << endl;
	cout << endl;
	
	return 0;
}