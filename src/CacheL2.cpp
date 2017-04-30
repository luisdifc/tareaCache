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

	if (this->memory[index].valid == 1) {
		if (trans.tagComparator(this->memory[index].tag, tag, this->tagSize) && this->memory[index].valid) 
			result = 1;
	}

	return result;
}

void CacheL2::blockFromMemory (int* dir) {
    int index = trans.binToDec(trans.L2Index(dir), this->indexSize);    
    this->memory[index].valid = 1;
    int* tag = trans.L2Tag(dir);

    this->memory[index].tag = tag;
    for (int i = 0; i < 256; ++i)
			this->memory[index].data[i] = 1;
}

void CacheL2::write(int index, int* tag, TwoWaySetLine* set, int tagL1, int tagL1Size) {
	this->memory[index].valid = 1;
	this->memory[index].tag = tag;

	if (trans.binToDec(set->tag0, tagL1Size) == tagL1) 
		this->memory[index].data = set->data0;
	else
		this->memory[index].data = set->data1;
}
