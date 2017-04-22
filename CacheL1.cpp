#include "CacheL1.h"

CacheL1::CacheL1() {

}

CacheL1::~CacheL1() {

}

void CacheL1::write (int* dir) {
	// int index = trans.binToDec(trans.L1Index(dir), index);

	// memory[index].tag0 = trans.L1Tag(dir);


	// int offset = trans.binToDec(trans.L1Offset(dir), 5);
	// for (int i = 0; i < index; ++i)
	// 	memory[index].data0[(offset * index) + i] = 1;
}

void CacheL1::read () { 
	cout << "El dato esta en Cache L1, hay un HIT!";
	this->hits++;
}

char CacheL1::mesiState (int* dir) {
	int wBlock = -1; //si wblock  = 0, bloque 0, si wBlock = 1, bloque 1, wBlocl = -1, no esta
	int index = trans.binToDec(trans.L1Index(dir), this->index);
	int* tag = trans.L1Tag(dir);

	if (trans.tagComparator(this->memory[index].tag0, tag, this->tagSize))
		wBlock = 0;
	else if (trans.tagComparator(this->memory[index].tag1, tag, this->tagSize))
		wBlock = 1;

	if (wBlock == -1)
		return 'N';
	else if (wBlock == 0)
		return trans.binToMesi(this->memory[index].MESI0);
	else
		return trans.binToMesi(this->memory[index].MESI1);
}

void CacheL1::L2WriteL1 (MPLine* L2Line, int* dir, int bloque) {
	int index = trans.binToDec(trans.L1Index(dir), index);
	if (bloque == 0) {
		this->memory[index].data0 = L2Line->data;
		this->memory[index].tag0 = trans.L1Tag(dir);
	}
	else {
		this->memory[index].data1 = L2Line->data;	
		this->memory[index].tag1 = trans.L1Tag(dir);
	}
}