#include "../include/CampusGraph.h"

// Add a building to the campus
void CampusGraph::addBuilding(string name) {
    buildings.push_back(name);
    connections.push_back(vector<int>());
}

// find the building by name
int CampusGraph::findBuilding(string name) {
    for (int i = 0; i < buildings.size(); i++) {
        if (buildings[i] == name) {
            return i;
        }
    }
    return -1;
}

// Connect two campus buildings
void CampusGraph::addConnection(string building1, string building2) {
    int a = findBuilding(building1);
    int b = findBuilding(building2);

    if (a == -1 || b == -1 || a == b) {
        cout << "Invalid connection." << endl;
        return;
    }

    for (int neighbor : connections[a]) {
        if (neighbor == b) {
            cout << "Connection already exists." << endl;
            return;
        }
    }

    connections[a].push_back(b);
    connections[b].push_back(a);
}


