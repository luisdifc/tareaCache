#ifndef TWOWAYSETLINE_H
#define TWOWAYSETLINE_H

#include <iostream>

using namespace std;

class TwoWaySetLine {

public:
    int LRU0;
    int LRU1;

    int MESI0 [2];
    int MESI1 [2];

    int tag0 [19];
    int tag1 [19];

    int data0 [256];
    int data1 [256];

public:
    TwoWaySetLine();
    virtual ~TwoWaySetLine();

    void printAll();
};

#endif /* TWOWAYSETLINE_H */

