#include <iostream>

#include "CacheL1.h"

using namespace std;

int main(int argc, char** argv) {
    CacheL1 cache0;
    CacheL1 cache1;

    cache0.memory[55].printAll();

    return 0;
}
