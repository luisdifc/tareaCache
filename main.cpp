#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"
#include "Translator.h"

using namespace std;

int main(int argc, char** argv) {
    //variables
    int* binDir;
    string line;
    int read = 1;  //!read = write
    ifstream dataFile1;
    ifstream dataFile2;
    int notificacionInvalidos = 0;

    //instancias
    Translator trans;
    CacheL1* cache0 = new CacheL1();
    CacheL1* cache1 = new CacheL1();
    CacheL2* shared = new CacheL2();

    //abrimos los archivos con direccciones
    trans.openFile(argv[1], dataFile1);
    trans.openFile(argv[2], dataFile2);

    cout << endl << "---------------------------------" << endl << endl;

    //leemos las lineas
    for (int index = 1; !dataFile2.eof() || !dataFile1.eof(); ++index) {

        //leemos las lineas de ambos cores "en paralelo"
        if (index % 4 != 0){
            if (!dataFile1.eof()) {
                line = trans.readLine(argv[1], dataFile1);
                cout << "Core 1 working..." << endl;
                cout << "File line to be processed: " << line << endl;

                binDir = trans.HexToBin(line);
                cout << "Memory Address: ";
                for (int i = 0; i < 32; ++i) {
                    cout << binDir[i];
                }
                cout << endl;

                // if (trans.writeOrRead(line))
                //     read = 0;
                read = !trans.writeOrRead(line);

                cache0->mainFunction(cache1, shared, binDir, read, notificacionInvalidos);
                cout << endl << "---------------------------------" << endl << endl;
            }
        } else {
            if (!dataFile2.eof()) {
                cout << "Core 2 working..." << endl;
                line = trans.readLine(argv[2], dataFile2);
                cout << "File line to be processed: " << line << endl;

                binDir = trans.HexToBin(line);
                cout << "Memory Address: ";
                for (int i = 0; i < 32; ++i) {
                    cout << binDir[i];
                }
                cout << endl;

                // if (trans.writeOrRead(line))
                //     read = 0;
                read = !trans.writeOrRead(line);

                cache1->mainFunction(cache0, shared, binDir, read, notificacionInvalidos);
                cout << endl << "---------------------------------" << endl << endl;
            }
        }
    }

    trans.closeFile(argv[1], dataFile1);
    trans.closeFile(argv[2],dataFile2);

    cout << "Core 1:\n\tHits en cache L1: " << cache0->hits  << "\n\tMisses en L1: " << cache0->misses << endl;
    cout << "Core 2:\n\tHits en cache L1: " << cache1->hits  << "\n\tMisses en L1: " << cache1->misses << endl;
    cout << "Cache en L2:\n\tHits: " << shared->hits << "\n\tMisses: " << shared->misses << endl;
    cout << "Combinación de estados inválidos: "  << notificacionInvalidos << endl;

    delete[] binDir;
    delete cache0;
    delete cache1;
    delete shared;

    return 0;
}
