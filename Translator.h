#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <fstream>
#include <iostream>
#include "TwoWaySetLine.h"

using namespace std;

class Translator {

public:
    //string line;
    ifstream dataFile;

public:
    Translator();
    virtual ~Translator();

    //void reader(char* fileName);
    void openFile (char* fileName);
    string readLine (char* fileName);
    void closeFile (char* fileName);
    int* HexToBin(char Hex, int* bin);

};

#endif /* TRANSLATOR_H */
