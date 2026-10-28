#include "../include/CampusGraph.h"

// add a building to the campus
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

// connecting two campus buildings
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

 // display buildings and their connections
void CampusGraph::showGraph() {
    if (buildings.empty()) {
        cout << "No buildings available." << endl;
        return;
    }

    for (int i = 0; i < buildings.size(); i++) {
        cout << buildings[i] << ": ";

        if (connections[i].empty()) {
            cout << "(no connections)";
        } else {
            for (int j : connections[i]) {
                cout << buildings[j] << " ";
            }
        }

        cout << endl;
    }
}

// display building and connection statistics
void CampusGraph::showStats() {
    int totalConnections = 0;

    cout << "Total buildings: " << buildings.size() << endl;

    for (int i = 0; i < buildings.size(); i++) {
        int degree = connections[i].size();

        cout << buildings[i] << " - Degree: " << degree << endl;

        totalConnections += degree;
    }

    cout << "Total connections: " << totalConnections / 2 << endl;
}

#include <queue>

// finding reachable buildings using BFS
void CampusGraph::bfs(string start) {
    int s = findBuilding(start);

    if (s == -1) {
        cout << "Building not found: " << start << endl;
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), 0);
    queue<int> q;

    visited[s] = true;
    q.push(s);

    int count = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << buildings[current]
             << " (distance " << distance[current] << ")" << endl;

        count++;

        for (int next : connections[current]) {
            if (!visited[next]) {
                visited[next] = true;
                distance[next] = distance[current] + 1;
                q.push(next);
            }
        }
    }

    cout << "Reachable: " << count
         << " of " << buildings.size() << " buildings" << endl;
}



