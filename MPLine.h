#ifndef MPLINE_H
#define MPLINE_H

#include <iostream>

using namespace std;

class MPLine {

public:
    int valid, dirty;
    int tag [19];
    int data [256];

public:
    MPLine();
    virtual ~MPLine();

    void printAll();
};

#endif /* MPLINE_H */

