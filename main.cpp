#include <iostream>

#include "CacheL1.h"
#include "CacheL2.h"

using namespace std;

int main(int argc, char** argv) {
    CacheL1 cache0;
    CacheL1 cache1;

    CacheL2 sharedCache;

    cache0.memory[55].printAll();
    cout << "--------------------------------------------" << endl;
    sharedCache.memory[3456].printAll();

    return 0;
}
