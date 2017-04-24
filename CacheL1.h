#ifndef CACHEL1_H
#define CACHEL1_H

#include <iostream>

#include "CacheL2.h"
#include "MPLine.h"
#include "Translator.h"
#include "TwoWaySetLine.h"

using namespace std;

class CacheL1 {

public:
    TwoWaySetLine memory[256];
    Translator trans;
    int index = 8;
    int tagSize = 19;
    int hits = 0;
    int misses = 0;

public:
    CacheL1();
    virtual ~CacheL1();
    void writeExistenTag (int currentIndexL1, int currentTagL1, int currentOffset);
    void read ();
    char mesiState (int* dir);
    void blockFromL2(int currentIndexL1, int currentIndexL2, MPLine* L2Line, int* binDir, char newState);
    void L2WriteL1 (MPLine* L2Line, int* dir, int bloque);
    void changeMESI(int currentIndexL1, char newState, int block);
    void mainFunction(CacheL1* cache1, CacheL2* shared, int* binDir, int read);
   // void protocolo (CacheL1* cache0, CacheL1* cache1, CacheL2* shared, int* dir);
};

#endif /* CACHEL1_H */
