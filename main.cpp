#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"

using namespace std;

int* HexToBin(char Hex, int* bin) {
    for (size_t index = 0; index < 4; index++) {
        bin[index] = 0;
    }
    switch(Hex) {
        case '0': break; //"0000"
        case '1': bin[0] = 1; break;//"0001"
        case '2': bin[1] = 1; break;//"0010"
        case '3': bin[1] = bin[0] = 1; break;//"0011"
        case '4': bin[2] = 1; break;//"0100"
        case '5': bin[2] = bin[0] = 1; break;//"0101"
        case '6': bin[2] = bin[1] = 1; break;//"0110"
        case '7': bin[2] = bin[1] = bin[0] = 1; break;//"0111"
        case '8': bin[3] = 1; break;//"1000"
        case '9': bin[3] = bin[0] = 1; break;//"1001"
        case 'A': bin[3] = bin[1] = 1; break; //"1010"
        case 'B': bin[3] = bin[1] = bin[0] = 1; break;//"1011"
        case 'C': bin[3] = bin[2] = 1; break;//"1100"
        case 'D': bin[3] = bin[2] = bin[0] = 1; break;//"1101"
        case 'E': bin[3] = bin[2] = bin[1] = 1; break;//"1110"
        case 'F': bin[3] = bin[2] = bin[1] = bin[0] = 1; break;//"1111"
    }
    return bin;
}

int main(int argc, char** argv) {
    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    cache0.memory[55].printAll();
    cout << "--------------------------------------------" << endl;
    sharedCache.memory[3456].printAll();

    return 0;
}
