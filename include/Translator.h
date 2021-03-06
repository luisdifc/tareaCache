#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include "TwoWaySetLine.h"

using namespace std;

class Translator {

public:
    //string line;
    // ifstream dataFile;

public:
    Translator();
    virtual ~Translator();

    //void reader(char* fileName);
    void openFile (char* fileName, ifstream& dataFile);
    string readLine (char* fileName, ifstream& dataFile);
    void closeFile (char* fileName, ifstream& dataFile);
    int binToDec (int* binary, int size);
    int* HexToBin(string Hex);
    int* L1Tag (int* dir);
    int* L1Index (int* dir);
    int* L1Offset (int* dir);
    int* L2Tag (int* dir);
    int* L2Index (int* dir);
    int* L2Offset (int* dir);
    int tagComparator (int* cacheTag, int* dirTag, int size);
    int writeOrRead (string line);
    char binToMesi (int* mesi);
    int sizeOfString (string line);
    string modifyLine (string line, int size);
};

#endif /* TRANSLATOR_H */
