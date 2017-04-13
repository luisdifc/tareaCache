#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"
#include "Translator.h"

using namespace std;

int main(int argc, char** argv) {
    int* prueba;
    int* l1Tag;
    int* l1Index;
    int* l1Offset;

    Translator trans;

    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    //abro el archivo para leer direcciones 
    trans.openFile(argv[1]);
    prueba = trans.HexToBin(trans.readLine(argv[1]));
    trans.closeFile(argv[1]);
    
    //impresion de la prueba
    cout << "Memory Address: 0x";
    for (int i = 0; i < 32; ++i) {
        cout << prueba[i];
    }
    cout << endl;

    l1Tag = trans.L1Tag(prueba);
    cout << "Tag: ";
    for (int i = 0; i < 19; ++i) {
        cout << l1Tag[i];
    }
    cout << endl;


    l1Index = trans.L1Index(prueba);
    cout << "Index: ";
    for (int i = 0; i < 8; ++i) {
        cout << l1Index[i];
    }
    cout << endl;

    l1Offset = trans.L1Offset(prueba);
    cout << "Offset: ";
    for (int i = 0; i < 5; ++i) {
        cout << l1Offset[i];
    }
    cout << endl;

    cache0.write(prueba);

    delete[] prueba;
    delete[] l1Tag;
    delete[] l1Index;
    delete[] l1Offset;

    cache0.memory[144].printAll();
    cout << "--------------------------------------------" << endl;
    //sharedCache.memory[3456].printAll();

    return 0;
}
