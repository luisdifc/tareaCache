#include "CacheL1.h"

CacheL1::CacheL1() {

}

CacheL1::~CacheL1() {

}

void CacheL1::writeExistenTag (int currentIndexL1, int currentTagL1, int currentOffset) {
	int tempTag = trans.binToDec(this->memory[currentIndexL1].tag0, this->tagSize);

    if(tempTag == currentTagL1) {
    	this->memory[currentIndexL1].LRU0 = 1;
		this->memory[currentIndexL1].LRU1 = 0;
        for (int i = 0; i < 8; ++i)
			this->memory[currentIndexL1].data0[(currentOffset * 8) + i] = 1;
	} else {
		this->memory[currentIndexL1].LRU0 = 0;
		this->memory[currentIndexL1].LRU1 = 1;
		for (int i = 0; i < 8; ++i)
			this->memory[currentIndexL1].data1[(currentOffset * 8) + i] = 1;
	}
}

void CacheL1::read (int tag, int index) {
	this->hits++;
	if (trans.binToDec(this->memory[index].tag0, this->tagSize) == tag) {
		this->memory[index].LRU0 = 1;
		this->memory[index].LRU1 = 0;
	}
	else {
	    this->memory[index].LRU0 = 0;
		this->memory[index].LRU1 = 1;
	}


}

char CacheL1::mesiState (int* dir) {
	int wBlock = -1; //si wblock  = 0, bloque 0, si wBlock = 1, bloque 1, wBlocl = -1, no esta
	int index = trans.binToDec(trans.L1Index(dir), this->index);
	int* tag = trans.L1Tag(dir);

	//cout << "Tag0 = " << trans.binToDec(this->memory[index].tag0, this->tagSize) << "\nTag1 = " << 
	//trans.binToDec(this->memory[index].tag1, this->tagSize) << "\nCurrent tag = " << trans.binToDec(tag, this->tagSize) << endl;
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
	int index = trans.binToDec(trans.L1Index(dir), this->index);
    int tag = trans.binToDec(trans.L1Tag(dir), this->tagSize);    
    if (bloque == 0) {
    	this->memory[index].data0 = L2Line->data;
		this->memory[index].tag0 = trans.L1Tag(dir);
	}
	else {
		this->memory[index].data1 = L2Line->data;
		this->memory[index].tag1 = trans.L1Tag(dir);
	}
}   

void CacheL1::blockFromL2(int currentIndexL1, int currentIndexL2, MPLine* L2Line, int* binDir, char newState) {
    if (this->memory[currentIndexL1].LRU0 == 0) {
        this->memory[currentIndexL1].LRU0 = 1;
		this->memory[currentIndexL1].LRU1 = 0;
		L2WriteL1(L2Line, binDir, 0);
        changeMESI(currentIndexL1, newState, 0);
    } else { //escribimos en el bloque 1
		this->memory[currentIndexL1].LRU0 = 0;
		this->memory[currentIndexL1].LRU1 = 1;
		L2WriteL1(L2Line, binDir, 1);
		changeMESI(currentIndexL1, newState, 1);
	}
}

void CacheL1::changeMESI(int currentIndexL1, char newState, int block) {
	if(block == 0) {
		if(newState == 'M') {
			this->memory[currentIndexL1].MESI0[0] = 0;
			this->memory[currentIndexL1].MESI0[1] = 1;
		} else if(newState == 'E') {
			this->memory[currentIndexL1].MESI0[0] = 1;
			this->memory[currentIndexL1].MESI0[1] = 0;
		} else if(newState == 'S') {
			this->memory[currentIndexL1].MESI0[0] = 1;
			this->memory[currentIndexL1].MESI0[1] = 1;
		} else if(newState == 'I') {
			this->memory[currentIndexL1].MESI0[0] = 0;
			this->memory[currentIndexL1].MESI0[1] = 0;
		}
	} else {
		if(newState == 'M') {
			this->memory[currentIndexL1].MESI1[0] = 0;
			this->memory[currentIndexL1].MESI1[1] = 1;
		} else if(newState == 'E') {
			this->memory[currentIndexL1].MESI1[0] = 1;
			this->memory[currentIndexL1].MESI1[1] = 0;
		} else if(newState == 'S') {
			this->memory[currentIndexL1].MESI1[0] = 1;
			this->memory[currentIndexL1].MESI1[1] = 1;
		} else if(newState == 'I') {
			this->memory[currentIndexL1].MESI1[0] = 0;
			this->memory[currentIndexL1].MESI1[1] = 0;
		}
	}
}

void CacheL1::mainFunction(CacheL1* cache1, CacheL2* shared, int* binDir, int read, int& notify) {

	//Variables a utiliar.
	//cout << "First" << endl;
    char mesiState = this->mesiState(binDir); //buscamos estado de mesi. Si no esta devuelve 'N'
    //cout << "Second" << endl;
	char mesiStateOtherCache = cache1->mesiState(binDir);
	int tempTag;
	int currentIndexL1 = trans.binToDec(trans.L1Index(binDir), this->index);
	int currentTagL1 = trans.binToDec(trans.L1Tag(binDir), this->tagSize);
	int currentIndexL2 = trans.binToDec(trans.L2Index(binDir), shared->indexSize);
	int currentTagL2 = trans.binToDec(trans.L2Tag(binDir), shared->tagSize);
	int currentOffset = trans.binToDec(trans.L1Offset(binDir), this->offset);

	cout << "MESI state: " << mesiState << endl;

	if (read) {
		//cout << "LECTURA" << endl;
		if (mesiState == 'E' || mesiState == 'S' || mesiState == 'M') {
			cout << "Hit en cache L1!!" << endl;
			this->read(currentTagL1, currentIndexL1);
		} else { //Serian los casos 'N' o 'I'. Tengo que traerlo de L2 o de mem
			//verificar si el tag esta en el otro cache y que estado tiene
			cout << "Miss en cache L1!!" << endl;
			this->misses++;
			//si no esta en el otro cache
			if (mesiStateOtherCache == 'N' || mesiStateOtherCache == 'I'){ //buscarlo en L2
				if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1

					/////////////////////////////////////////////////////////
					cout << "Hit en cache L2!!" << endl;
					shared->hits++;
                    this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'E');
				} else { //Hay un miss en el shared Hay que traer el dato de memoria principal
                    cout << "Miss en cache L2!!" << endl;
                    shared->misses++;
                    shared->blockFromMemory(binDir);
                    this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'E');
				}
			} else if (mesiStateOtherCache == 'E') { //Esta en el otro cache en estado Exclusive.
				tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, cache1->tagSize);
				if(tempTag == currentTagL1) //Cambiar a estado Shared en OtherCache
					cache1->changeMESI(currentIndexL1, 'S', 0);
				else
					cache1->changeMESI(currentIndexL1, 'S', 1);

				//Traer el dato al cache en cuestion y lo pongo en estado Shared
				if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
					cout << "Hit en cache L2!!" << endl;
					shared->hits++;
                    this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
				} else { //Hay un miss en el shared Hay que traer el dato de memoria principal
                    cout << "Miss en cache L2!!" << endl;
                    shared->misses++;
                    shared->blockFromMemory(binDir);
                    this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
				}
			} else if (mesiStateOtherCache == 'M') { //Esta en el otro caché en estado Modified.
				//Lo escribo en memoria principal
				shared->write(currentIndexL2, trans.L2Tag(binDir), &cache1->memory[currentIndexL1], currentTagL1, cache1->tagSize);
				cout << "Miss en cache L2!!" << endl;
                shared->misses++;
				//Paso su estado a Shared en other caché
				tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, cache1->tagSize);
				if(tempTag == currentTagL1)
					cache1->changeMESI(currentIndexL1, 'S', 0);
				else
					cache1->changeMESI(currentIndexL1, 'S', 1);

				//Traigo el dato al cache en cuestion y lo pongo en estado Shared
				if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
					this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
				} 
			}
		}
	}
	else { //write
		//cout << "ESCRITURA" << endl;
		if (mesiState == 'E') {
			//Escribo el dato en el caché.
			this->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);

			//Cambio su estado a Modified.
			tempTag = trans.binToDec(this->memory[currentIndexL1].tag0, this->tagSize);
			if(tempTag == currentTagL1)
				this->changeMESI(currentIndexL1, 'M', 0);
			else
				this->changeMESI(currentIndexL1, 'M', 1);
		} else if (mesiState == 'S' || mesiState == 'I') {
			//Escribo el dato en el caché.
			this->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);

			//Cambio su estado a Modified.
			tempTag = trans.binToDec(this->memory[currentIndexL1].tag0, this->tagSize);
			if(tempTag == currentTagL1)
				this->changeMESI(currentIndexL1, 'M', 0);
			else
				this->changeMESI(currentIndexL1, 'M', 1);

			//Invalido el dato en el otro caché, si estuviera.
			if(cache1->mesiState(binDir) != 'N') {
				tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, this->tagSize);
				if(tempTag == currentTagL1)
					cache1->changeMESI(currentIndexL1, 'I', 0);
				else
					cache1->changeMESI(currentIndexL1, 'I', 1);
			}
		} else if(mesiState == 'M') {
			//Escribo el dato en el caché.
			this->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);
		} else { //Caso donde el estado sea N, es decir el tag no esta en el cacheL1
			//Invalido el dato en el otro caché si estuviera.
			if(mesiStateOtherCache != 'N') {
				tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, this->tagSize);
				if(tempTag == currentTagL1)
					cache1->changeMESI(currentIndexL1, 'I', 0);
				else
					cache1->changeMESI(currentIndexL1, 'I', 1);
			}

			//Traigo el bloque de L2 al L1
			if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
				this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
				cout << "Hit en cache L2, escritura" << endl;
                //shared->hits++;
			} else { //Hay un miss en el shared Hay que traer el bloque de memoria principal
                shared->blockFromMemory(binDir);
                cout << "Miss en cache L2, escritura" << endl;
                //shared->misses++;
                this->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'M');
			}

            //Escribo el dato en el caché.
			// ESTO ESTA BIEN, PERO HAY QUE HACER EL ELSE DE ARRIBA PARA QUE NO SE CAIGA EL PROGRAMA.
			this->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);
            
            //Cambio su estado a Modified.
			tempTag = trans.binToDec(this->memory[currentIndexL1].tag0, this->tagSize);

			if(tempTag == currentTagL1)
				this->changeMESI(currentIndexL1, 'M', 0);
			else
				this->changeMESI(currentIndexL1, 'M', 1);
		}
	}

	mesiState = this->mesiState(binDir);
	mesiStateOtherCache = cache1->mesiState(binDir);


	if ( ((mesiState == 'M') && (mesiStateOtherCache == 'M')) ||
		((mesiState == 'M') && (mesiStateOtherCache == 'E')) ||
		((mesiState == 'M') && (mesiStateOtherCache == 'S')) ||
		((mesiState == 'E') && (mesiStateOtherCache == 'M')) ||
		((mesiState == 'E') && (mesiStateOtherCache == 'E')) ||
		((mesiState == 'E') && (mesiStateOtherCache == 'S')) ||
		((mesiState == 'S') && (mesiStateOtherCache == 'M')) ||
		((mesiState == 'S') && (mesiStateOtherCache == 'E')) )
		notify++;
		
	cout << "This core MESI state at the end of the process: " << mesiState << endl;
	cout << "Other core MESI state at the end of the process: " << mesiStateOtherCache << endl;

}