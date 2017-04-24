#include "CacheL2.h"

CacheL2::CacheL2() {

}

CacheL2::~CacheL2() {

}

//0 = miss, 1 = hit
int CacheL2::read (int* dir) {
	int result = 0;
	int index = trans.binToDec(trans.L2Index(dir), this->indexSize);
	int* tag = trans.L2Tag(dir);

	if (trans.tagComparator(this->memory[index].tag, tag, this->tagSize) && this->memory[index].valid) {
		cout << "Hit en cache L2!!" << endl;
		result = 1;
		this->hits++;
	}
	else {
		cout << "Miss en cache L2!!" << endl;
		this->misses++;
	}
	return result;
}
