#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// storing campus buildings and their connections
class CampusGraph {
private:
    vector<string> buildings;
    vector<vector<int>> connections;

public:
    void addBuilding(string name);    
    int findBuilding(string name);
    void loadBuildings(string filename);
    void addConnection(string building1, string building2);
    void showBuildings();
    void showGraph();
    void showStats();
    void bfs(string start);
};
