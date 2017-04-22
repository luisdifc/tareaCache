#ifndef CACHEL1_H
#define CACHEL1_H

#include <iostream>

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
    void write (int* dir);
    void read ();
    char mesiState (int* dir);
    void L2WriteL1 (MPLine* L2Line, int* dir, int bloque);
};

#endif /* CACHEL1_H */

