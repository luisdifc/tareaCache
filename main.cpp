#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"
#include "Translator.h"

using namespace std;

int main(int argc, char** argv) {
    int* binDir;
    int* l1Tag;
    int* l1Index;
    int* l1Offset;
    string line;

    Translator trans;

    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    //abro el archivo para leer direcciones 
    trans.openFile(argv[1]);
    line = trans.readLine(argv[1]);
    binDir = trans.HexToBin(line);
    trans.closeFile(argv[1]);


    cout << "File line to be processed: " <<line << endl;
    //impresion de la binDir
    cout << "Memory Address: ";
    for (int i = 0; i < 32; ++i) {
        cout << binDir[i];
    }
    cout << endl;

    //ver si leo o escribo
    if (trans.writeOrRead(line))
        cache0.write(binDir);
    else
        cache0.read(binDir);
    

    delete[] binDir;

    //impresion cacheL1
    cache0.memory[144].printAll();

    return 0;
}
