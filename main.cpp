#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"
#include "Translator.h"

using namespace std;

int main(int argc, char** argv) {
    Translator trans;

    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    trans.openFile(argv[1]);
    cout << trans.readLine(argv[1]) << endl;
    cout << trans.readLine(argv[1]) << endl;

    trans.closeFile(argv[1]);

    cache0.memory[55].printAll();
    cout << "--------------------------------------------" << endl;
    sharedCache.memory[3456].printAll();

    return 0;
}
