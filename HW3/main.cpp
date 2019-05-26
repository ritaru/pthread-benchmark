#include "threadBench.hpp"

#define TEST_CASE 100000000UL

using namespace std;

int main(void) {
	cout << "# Log calculation test (" << TEST_CASE << " calculations)" << endl;
	cout << "# Using " << ((double)TEST_CASE / 44739242.667) << "GB of memory" << endl << endl;
	
	threadBench *singleTest = new threadBench(TEST_CASE);
	if (singleTest->benchmark() == -1)
		return -1;
	delete(singleTest);

	for (int i = 1; i <= 8; i++) {
		threadBench *multiTest = new threadBench(TEST_CASE, i);
		if (multiTest->benchmark() == -1)
			return -1;
		delete(multiTest);
	}

	system("PAUSE");
	return 0;
}