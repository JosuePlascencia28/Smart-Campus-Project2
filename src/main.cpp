#include <iostream>
#include <string>
#include "../include/CampusGraph.h"
#include "../include/HashTable.h"


using namespace std;

int main(int argc, char* argv[]) {
    cout << "Welcome to Smart Campus Navigation and Facility Analytics System" << endl;

    string dataFolder = "data/";

    if (argc > 1) {
        dataFolder = argv[1];
        if (dataFolder.back() != '/') {
            dataFolder += "/";
        }
    }

    CampusGraph campus;

    campus.loadBuildings(dataFolder + "buildings.txt");
    campus.loadConnections(dataFolder + "connections.txt");
        
    HashTable facilities;
    
    facilities.loadFacilities(dataFolder + "facilities.txt", campus);
    facilities.showFacilities();


    campus.showGraph();
    campus.showStats();

    return 0;
}
