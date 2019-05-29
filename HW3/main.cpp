#include "threadBench.hpp"
#include <iomanip>

#define TEST_CASE 2000000UL

using namespace std;

int main(void) {
	cout << "# Log calculation test (" << TEST_CASE << " calculations)" << endl;
	cout << "# Using " << ((double)TEST_CASE / 44739242.667) << "GB of memory" << endl << endl;
	double avgNoThreadTime = 0,
		avgThreadTime = 0;
	double noThreadResult = 0,
		threadResult = 0;

	cout << "100 tests avg" << endl;
	cout.setf(ios::fixed, ios::floatfield);

	for (int i = 0; i < 100; i++) {
		threadBench *singleTest = new threadBench(TEST_CASE);
		if (singleTest->benchmark() == -1)
			return -1;
		avgNoThreadTime += singleTest->duration / 100.0;
		noThreadResult += singleTest->result / 100.0;
		delete(singleTest);
	}
	
	cout << "No thread avg: ";
	cout << setw(9) << setfill('0') << avgNoThreadTime;
	cout << "ms ";
	cout << "checkSum: " << noThreadResult << endl;

	for (int j = 1; j <= 8; j*=2) {
		avgThreadTime = 0;
		threadResult = 0;
		for (int i = 0; i < 100; i++) {
			threadBench *multiTest = new threadBench(TEST_CASE, j);
			if (multiTest->benchmark() == -1)
				return -1;
			avgThreadTime += multiTest->duration / 100.0;
			threadResult += multiTest->result / 100.0;
			delete(multiTest);
		}
		cout << j << " threads " << "avg: ";
		cout << setw(9) << setfill('0') << avgThreadTime;
		cout << "ms ";
		cout << "checkSum: " << threadResult << endl;
	}
	system("PAUSE");
	return 0;
}