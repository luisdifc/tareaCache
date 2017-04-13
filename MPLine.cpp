#include "MPLine.h"

MPLine::MPLine() {
	valid = 0;
	dirty = 0;

	tag = new int[19];
	for (int index = 0; index < 19; ++index) 
		tag[index] = 0;
	
	data = new int [256];
	for (int index = 0; index < 256; ++index) 
		data[index] = 0;
}

MPLine::~MPLine() {
	delete [] tag;
	delete[] data;
}

void MPLine::printAll() {
	
	cout << "VALID : " << valid << endl;
	cout << "DIRTY : " << dirty << endl;

	cout << "tag: ";
	for (int index = 0; index < 19; ++index) 
		cout << tag[index] << "   ";
	
	cout << endl;

	cout << "data: ";
	for (int index = 0; index < 256; ++index) 
		cout << data[index] << "   ";
	
	cout << endl;

}