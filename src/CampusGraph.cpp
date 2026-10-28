#include "../include/CampusGraph.h"

// Add a building to the campus
void CampusGraph::addBuilding(string name) {
    buildings.push_back(name);
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

