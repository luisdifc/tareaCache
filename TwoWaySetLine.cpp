#include "TwoWaySetLine.h"

TwoWaySetLine::TwoWaySetLine() {
	LRU0 = 0;
	LRU1 = 0;

	for (int index = 0; index < 2; ++index) {
		MESI0[index] = 0;
		MESI1[index] = 0;
	}

	for (int index = 0; index < 19; ++index) {
			TAG0[index] = 0;
			TAG1[index] = 0;
	}

	for (int index = 0; index < 256; ++index) {
			DATOS0[index] = 0;
			DATOS1[index] = 0;
	}
}

TwoWaySetLine::~TwoWaySetLine() {

}

void TwoWaySetLine::printAll() {
	
	cout << "LRU 0: " << LRU0 << endl;

	cout << "MESI 0: ";
	for (int index = 0; index < 2; ++index) {
		cout << MESI0[index] << "   ";
	}
	cout << endl;

	cout << "TAG 0: ";
	for (int index = 0; index < 19; ++index) {
		cout << TAG0[index] << "   ";
	}
	cout << endl;

	cout << "DATOS 0: ";
	for (int index = 0; index < 256; ++index) {
			cout << DATOS0[index] << "   ";
	}
	cout << endl;

}