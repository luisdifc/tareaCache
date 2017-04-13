#ifndef MPLINE_H
#define MPLINE_H

#include <iostream>

using namespace std;

class MPLine {

public:
    int valid, dirty;
    int* tag;
    int* data;

public:
    MPLine();
    virtual ~MPLine();

    void printAll();
};

#endif /* MPLINE_H */

