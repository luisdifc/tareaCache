#include "TwoWaySetLine.h"

TwoWaySetLine::TwoWaySetLine() {
	LRU0 = 0;
	LRU1 = 1;


	MESI0 = new int[2];
	MESI1 = new int[2];
	for (int index = 0; index < 2; ++index) {
		MESI0[index] = 0;
		MESI1[index] = 0;
	}

	tag0 = new int[19];
	tag1 = new int[19];
	for (int index = 0; index < 19; ++index) {
		tag0[index] = 0;
		tag1[index] = 0;
	}

	data0 = new int[256];
	data1 = new int[256];
	for (int index = 0; index < 256; ++index) {
		data0[index] = 0;
		data1[index] = 0;
	}
}

TwoWaySetLine::~TwoWaySetLine() {
	delete[] MESI0;
	delete[] MESI1;

	delete[] tag0;
	delete[] tag1;

	delete[] data0;
	delete[] data1;
}

void TwoWaySetLine::printAll() {
	
	cout << "LRU: " << LRU0 << endl;

	cout << "MESI: ";
	for (int index = 0; index < 2; ++index) 
		cout << MESI0[index];
	
	cout << endl;

	cout << "tag: ";
	for (int index = 0; index < 19; ++index) 
		cout << tag0[index];
	cout << endl;

	cout << "Data blocks: ";
	for (int index = 0; index < 256; ++index) {
		if (index %8 == 0) {
			cout << "\n";
			std::cout.width (2);
			cout << index / 8 << ": ";
		}
		cout << data0[index] << "   ";
	}
	
	cout << endl;

}