#include "../include/HashTable.h"
#include <iostream>
#include <cctype>
using namespace std;

// calculate a bucket number for a facility ID
int HashTable::hashFunction(string id) {
    int hash = 0;

    for (char c : id) {
        hash = (hash * 31 + c) % SIZE;
    }

    return hash;
}

// add a facility to the hash table
bool HashTable::insert(Facility facility) {
    string id = facility.id;

    // convert ID to uppercase
    for (char &c : id) {
        c = toupper(c);
    }

    facility.id = id;
    int index = hashFunction(id);

    for (Facility f : table[index]) {
        if (f.id == id) {
            return false;
        }
    }

    if (!table[index].empty()) {
        collisions++;
    }

    table[index].push_back(facility);
    entries++;

    return true;
}

