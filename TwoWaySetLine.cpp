#include "TwoWaySetLine.h"

TwoWaySetLine::TwoWaySetLine() {
	LRU0 = 0;
	LRU1 = 0;

	for (int index = 0; index < 2; ++index) {
		MESI0[index] = 0;
		MESI1[index] = 0;
	}

	for (int index = 0; index < 19; ++index) {
		tag0[index] = 0;
		tag1[index] = 0;
	}

	for (int index = 0; index < 256; ++index) {
		data0[index] = 0;
		data1[index] = 0;
	}
}

TwoWaySetLine::~TwoWaySetLine() {

}

void TwoWaySetLine::printAll() {
	
	cout << "LRU 0: " << LRU0 << endl;

	cout << "MESI 0: ";
	for (int index = 0; index < 2; ++index) 
		cout << MESI0[index] << "   ";
	
	cout << endl;

	cout << "tag 0: ";
	for (int index = 0; index < 19; ++index) 
		cout << tag0[index] << "   ";
	
	cout << endl;

	cout << "data 0: ";
	for (int index = 0; index < 256; ++index) 
		cout << data0[index] << "   ";
	
	cout << endl;

}