#ifndef CACHEL1_H
#define CACHEL1_H

#include <iostream>
#include "TwoWaySetLine.h"

using namespace std;

class CacheL1 {

public:
    TwoWaySetLine memory[256];

public:
    CacheL1();
    virtual ~CacheL1();

};

#endif /* CACHEL1_H */

