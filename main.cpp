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
    for (int index = 1; !dataFile2.eof(); ++index) {

        //leemos las lineas de ambos cores "en paralelo"
        if (index % 4 != 0){
            line = trans.readLine(argv[1], dataFile1);
            cout << "File line to be processed: " <<line << endl;

            binDir = trans.HexToBin(line);
            cout << "Memory Address: ";
            for (int i = 0; i < 32; ++i) {
                cout << binDir[i];
            }
            cout << endl;

            if (trans.writeOrRead(line))
                read = 0;
            cache1->mainFunction(cache0, shared, binDir, read);
            cout << endl << "---------------------------------" << endl << endl;
        } else {
            line = trans.readLine(argv[2], dataFile2);
            cout << "File line to be processed: " <<line << endl;

            binDir = trans.HexToBin(line);
            cout << "Memory Address: ";
            for (int i = 0; i < 32; ++i) {
                cout << binDir[i];
            }
            cout << endl;

            if (trans.writeOrRead(line))
                read = 0;
            cache0->mainFunction(cache1, shared, binDir, read);
            cout << endl << "---------------------------------" << endl << endl;
        }
    }

    trans.closeFile(argv[1], dataFile1);
    trans.closeFile(argv[2],dataFile2);

    delete[] binDir;
    delete cache0;
    delete cache1;
    delete shared;

/*

    //buscamos estado de mesi. Si no esta devuelve 'N'
    mesiState = cache0->mesiState(binDir);

    cout << "MESI state: " <<mesiState << endl;

    /////////////////////////////////////////////////////////////////

    //Variables a utiliar.
    int tempTag;
    int currentIndexL1 = trans.binToDec(trans.L1Index(binDir), cache0->index);
    int currentTagL1 = trans.binToDec(trans.L1Tag(binDir), cache0->tagSize);
    int currentIndexL2 = trans.binToDec(trans.L2Index(binDir), shared->indexSize);
    int currentTagL2 = trans.binToDec(trans.L2Tag(binDir), shared->tagSize);
    int currentOffset = trans.binToDec(trans.L1Offset(binDir), cache0->index);

    //ver si la linea de la direccion de entrada esta en cache
    //independientemente si es lectura o escritura
    if (mesiState == 'N') { //no estaba en el cache, TAG NO COINCIDE
        if (read) {
            cout << "Miss de cache L1..." << endl;
            //BUSCAR EN CACHE L2
        }
        //else  //write
            //cache0->write(binDir);

    }
    else { //la direccion si esta en el cache, tag coincide.
        if (read) {
            if (mesiState == 'E' || mesiState == 'S' || mesiState == 'M')
                cache0->read();
            else { //solo existe el caso 'I'. Tengo que traerlo de L2 o de mem
                //verificar si el tag esta en el otro cache y que estado tiene
                cache0->misses++;
                mesiStateOtherCache = cache1->mesiState(binDir);
                //si no esta en el otro cache
                if (mesiStateOtherCache == 'N' || mesiStateOtherCache == 'I'){ //buscarlo en L2
                    if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
                        cache0->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'E');
                    } else { //Hay un miss en el shared Hay que traer el dato de memoria principal

                    }
                } else if (mesiStateOtherCache == 'E') { //Esta en el otro cache en estado Exclusive.
                    tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, cache1->index);
                    if(tempTag == currentTagL1) //Cambiar a estado Shared en OtherCache
                        cache1->changeMESI(currentIndexL1, 'S', 0);
                    else
                        cache1->changeMESI(currentIndexL1, 'S', 1);

                    //Traer el dato al cache en cuestion y lo pongo en estado Shared
                    if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
                        cache0->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
                    } else { //Hay un miss en el shared Hay que traer el dato de memoria principal

                    }
                } else if (mesiStateOtherCache == 'M') { //Esta en el otro caché en estado Modified.
                    //Lo escribo en memoria principal


                    //Paso su estado a Shared en other caché
                    tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, cache1->index);
                    if(tempTag == currentTagL1)
                        cache1->changeMESI(currentIndexL1, 'S', 0);
                    else
                        cache1->changeMESI(currentIndexL1, 'S', 1);

                    //Traigo el dato al cache en cuestion y lo pongo en estado Shared
                    if (shared->read(binDir)) { //si lo encuentra en L2. Traer bloque a L1
                        cache0->blockFromL2(currentIndexL1, currentIndexL2, &shared->memory[currentIndexL2], binDir, 'S');
                    } else { //Hay un miss en el shared Hay que traer el dato de memoria principal

                    }
                }
            }
        }
        else { //write
            if (mesiState == 'E') {
                //Escribo el dato en el caché.
                cache0->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);

                //Cambio su estado a Modified.
                tempTag = trans.binToDec(cache0->memory[currentIndexL1].tag0, cache0->index);
                if(tempTag == currentTagL1)
                    cache0->changeMESI(currentIndexL1, 'M', 0);
                else
                    cache0->changeMESI(currentIndexL1, 'M', 1);
            } else if (mesiState == 'S' || mesiState == 'I') {
                //Escribo el dato en el caché.
                cache0->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);

                //Cambio su estado a Modified.
                tempTag = trans.binToDec(cache0->memory[currentIndexL1].tag0, cache0->index);
                if(tempTag == currentTagL1)
                    cache0->changeMESI(currentIndexL1, 'M', 0);
                else
                    cache0->changeMESI(currentIndexL1, 'M', 1);

                //Invalido el dato en el otro caché, si estuviera.
                if(cache1->mesiState(binDir) != 'N') {
                    tempTag = trans.binToDec(cache1->memory[currentIndexL1].tag0, cache0->index);
                    if(tempTag == currentTagL1)
                        cache1->changeMESI(currentIndexL1, 'I', 0);
                    else
                        cache1->changeMESI(currentIndexL1, 'I', 1);
                }
            } else if(mesiState == 'M') {
                //Escribo el dato en el caché.
                cache0->writeExistenTag(currentIndexL1, currentTagL1, currentOffset);
            }
        }
    }

    /////////////////////////////////////////////////////////////////
*/
    //impresion cacheL1
    //cache0->memory[144].printAll();

    return 0;
}
