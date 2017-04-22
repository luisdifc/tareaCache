#ifndef CACHEL2_H
#define CACHEL2_H

#include <iostream>

#include "MPLine.h"
#include "Translator.h"

using namespace std;

class CacheL2 {

public:
    MPLine memory[4096];
    Translator trans;
    int indexSize = 12;
    int tagSize = 15;
    int hits = 0;
    int misses = 0;

public:
    CacheL2();
    virtual ~CacheL2();

    int read (int* dir);

};

#endif /* CACHEL2_H */

