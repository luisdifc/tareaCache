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
    int read = 1;  //!read = write
    char mesiState = '0';
    char mesiStateOtherCache = '0';

    Translator trans;

    CacheL1 cachePrimerNivel0;
    CacheL1 cachePrimerNivel1;

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
        read = 0;

    if (!read)
        cachePrimerNivel0.write(binDir);



    //buscamos estado de mesi. Si no esta devuelve 'N'
    mesiState = cachePrimerNivel0.mesiState(binDir);

    cout << "MESI state: " <<mesiState << endl;
    
    /////////////////////////////////////////////////////////////////

    //ver si la linea de la direccion de entrada esta en cache
    //independientemente si es lectura o escritura
    if (mesiState == 'N') { //no estaba en el cache, TAG NO COINCIDE
        if (read) {
            cout << "Miss de cache L1..." << endl;
            //BUSCAR EN CACHE L2
        }
        else  //write
            cachePrimerNivel0.write(binDir);
        
    }
    else { //la direccion si esta en el cache, tag coincide. 
        if (read) {
            if (mesiState == 'E' || mesiState == 'S' || mesiState == 'M') 
                cachePrimerNivel0.read();
            else { //solo existe el caso 'I'. Tengo que traerlod e L2 o de mem
                //verificar si el tag esta en el otro cache y que estado tiene
                cachePrimerNivel0.misses++;
                mesiStateOtherCache = cachePrimerNivel1.mesiState(binDir);
                //si no esta en el otro cache 
                if (mesiStateOtherCache == 'N'){ //buscarlo en L2
                    if (sharedCache.read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
                        //escribimos en el bloque 0
                        if (cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].LRU0 == 0) {
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].LRU0 = 1;
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].LRU1 = 0;
                            cachePrimerNivel0.L2WriteL1(&sharedCache.memory[trans.binToDec(trans.L2Index(binDir), sharedCache.indexSize)], binDir, 0);
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].MESI0[0] = 1;
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].MESI0[1] = 0;
                        } else { //escribimos en el bloque 1
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].LRU0 = 0;
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].LRU1 = 1;
                            cachePrimerNivel0.L2WriteL1(&sharedCache.memory[trans.binToDec(trans.L2Index(binDir), sharedCache.indexSize)], binDir, 1);
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].MESI1[0] = 1;
                            cachePrimerNivel0.memory[trans.binToDec(trans.L1Index(binDir), cachePrimerNivel0.index)].MESI1[1] = 0;
                        }

                    }
                }
            }
        }
        else { //write

        }
    }

    /////////////////////////////////////////////////////////////////

    delete[] binDir;

    //impresion cacheL1
    //cachePrimerNivel0.memory[144].printAll();

    return 0;
}
