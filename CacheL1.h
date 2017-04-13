#ifndef CACHEL1_H
#define CACHEL1_H

#include <iostream>
#include "Translator.h"
#include "TwoWaySetLine.h"

using namespace std;

class CacheL1 {

public:
    TwoWaySetLine memory[256];
    Translator trans;

public:
    CacheL1();
    virtual ~CacheL1();
    void write (int* dir);
    void read (int* dir);

};

#endif /* CACHEL1_H */

