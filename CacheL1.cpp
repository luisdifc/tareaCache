#include "CacheL1.h"

CacheL1::CacheL1() {

}

CacheL1::~CacheL1() {

}

void CacheL1::write (int* dir) {
	int index = trans.binToDec(trans.L1Index(dir), 8);

	memory[index].tag0 = trans.L1Tag(dir);


	int offset = trans.binToDec(trans.L1Offset(dir), 5);
	for (int i = 0; i < 8; ++i)
		memory[index].data0[(offset * 8) + i] = 1;
}