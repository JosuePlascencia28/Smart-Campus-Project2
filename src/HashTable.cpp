#include "../include/HashTable.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

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
    
    if (!validID(id)) {
        cout << "Invalid facility ID: " << id << endl;
        return false;
    }
    
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
    facilities.push_back(facility);
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

// load facilities from a text file
void HashTable::loadFacilities(string filename, CampusGraph &campus) {
    ifstream file(filename);
    string line;
    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    while (getline(file, line)) {
        lineNumber++;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        stringstream ss(line);
        Facility f;

        getline(ss, f.id, '|');
        getline(ss, f.name, '|');
        getline(ss, f.building, '|');
        getline(ss, f.category);

        if (f.id.empty() || f.name.empty() ||
            f.building.empty() || f.category.empty()) {
            cout << filename << " line " << lineNumber
                 << ": Missing information." << endl;
            rejected++;
            continue;
        }

        int buildingIndex = campus.findBuilding(f.building);

        if (buildingIndex == -1) {
            cout << filename << " line " << lineNumber
                 << ": Unknown building " << f.building << endl;
            rejected++;
            continue;
        }

        if (insert(f)) {
            accepted++;
        } else {
            cout << filename << " line " << lineNumber
                 << ": Invalid or duplicate facility ID." << endl;
            rejected++;
        }
    }

    cout << filename << ": " << accepted
         << " accepted, " << rejected << " rejected." << endl;

    showStats();
}

 // display all accepted facilities
void HashTable::showFacilities() {
    if (facilities.empty()) {
        cout << "No facilities available." << endl;
        return;
    }

    cout << "Campus Facilities:" << endl;

    for (Facility f : facilities) {
        cout << f.id << " | "
             << f.name << " | "
             << f.building << " | "
             << f.category << endl;
    }

    cout << "Total facilities: "
         << facilities.size() << endl;
}


