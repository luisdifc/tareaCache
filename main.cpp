#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"
#include "Translator.h"

using namespace std;

int main(int argc, char** argv) {
    int* prueba;

    Translator trans;

    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    //abro el archivo para leer direcciones 
    trans.openFile(argv[1]);
    
    prueba = trans.HexToBin(trans.readLine(argv[1]));

    //impresion de la prueba
    for (int i = 0; i < 32; ++i) {
        cout << prueba[i];
    }
    cout << endl;
    delete[] prueba ;

    prueba = trans.HexToBin(trans.readLine(argv[1]));

    //impresion de la prueba
    for (int i = 0; i < 32; ++i) {
        cout << prueba[i];
    }
    cout << endl;
    delete[] prueba ;

    prueba = trans.HexToBin(trans.readLine(argv[1]));

    //impresion de la prueba
    for (int i = 0; i < 32; ++i) {
        cout << prueba[i];
    }
    cout << endl;
    delete[] prueba ;

    trans.closeFile(argv[1]);

    // cache0.memory[55].printAll();
    // cout << "--------------------------------------------" << endl;
    // sharedCache.memory[3456].printAll();

    return 0;
}
