#ifndef TWOWAYSETLINE_H
#define TWOWAYSETLINE_H

#include <iostream>

using namespace std;

class TwoWaySetLine {

public:
    int LRU0;
    int LRU1;

    int* MESI0;
    int* MESI1;

    int* tag0;
    int* tag1;

    int* data0;
    int* data1;

public:
    TwoWaySetLine();
    virtual ~TwoWaySetLine();

    void printAll();
};

#endif /* TWOWAYSETLINE_H */

