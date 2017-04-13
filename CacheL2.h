#ifndef CACHEL2_H
#define CACHEL2_H

#include <iostream>
#include "MPLine.h"

using namespace std;

class CacheL2 {

public:
    MPLine memory[4096];

public:
    CacheL2();
    virtual ~CacheL2();

};

#endif /* CACHEL2_H */

