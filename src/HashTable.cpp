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

bool HashTable::search(string id, Facility &result) {
    
    for (char &c : id) {
        c = toupper(c);
    }

    int index = hashFunction(id);

    for (Facility f : table[index]) {
        if (f.id == id) {
            result = f;
            return true;
        }
    }

    return false;
}

void HashTable::showStats() {
    cout << "Hash table capacity: " << SIZE << endl;
    cout << "Total entries: " << entries << endl;
    cout << "Total collisions: " << collisions << endl;
}

// Check if a facility ID is valid
bool HashTable::validID(string id) {
    if (id.length() != 4) {
        return false;
    }

    if (toupper(id[0]) != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (!isdigit(id[i])) {
            return false;
        }
    }

    return true;
}


