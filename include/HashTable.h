#pragma once

#include <string>
#include <vector>
using namespace std;

// stores information about a campus facility
struct Facility {
    string id;
    string name;
    string building;
    string category;
};

// custom hash table for searching facilities by ID
class HashTable {
private:
    static const int SIZE = 101;
    vector<Facility> table[SIZE];
    vector<Facility> facilities;
    int entries = 0;
    int collisions = 0;

    int hashFunction(string id);

public:
    bool insert(Facility facility);
    bool search(string id, Facility &result);
    void showStats();
    bool validID(string id); 
    void loadFacilities(string filename);
    void showFacilities();

};



