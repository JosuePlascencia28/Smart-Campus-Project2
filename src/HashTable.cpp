#include "../include/HashTable.h"
#include <iostream>
using namespace std;

// calculate a bucket number for a facility ID
int HashTable::hashFunction(string id) {
    int hash = 0;

    for (char c : id) {
        hash = (hash * 31 + c) % SIZE;
    }

    return hash;
}

