#include <iostream>
#include <string>
#include "../include/CampusGraph.h"
#include "../include/HashTable.h"
#include "../include/DepartmentTree.h"



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
        
    DepartmentTree departments;
    
    departments.loadDepartments(dataFolder + "departments.txt");


    
    int choice;
    
    do {
        cout << "\n===== SMART CAMPUS MENU =====" << endl;
        cout << "1. View all facilities" << endl;
        cout << "2. Search facility by ID" << endl;
        cout << "3. View campus graph" << endl;
        cout << "4. Display graph counts and degrees" << endl;
        cout << "5. Find reachable buildings (BFS)" << endl;
        cout << "6. Add department" << endl;
        cout << "7. Search department" << endl;
        cout << "8. Display department hierarchy" << endl;
        cout << "9. Run preorder traversal" << endl;
        cout << "10. Exit" << endl;
    
        cout << "Enter your choice: ";
        cin >> choice;
    
        if (choice == 1) {
            facilities.showFacilities();
        }
        else if (choice == 3) {
            campus.showGraph();
        }
        else if (choice == 4) {
            campus.showStats();
        }
        else if (choice == 8) {
            departments.showHierarchy();
        }
        else if (choice == 9) {
            departments.preorder();
        }
        else if (choice == 10) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice or option not added yet." << endl;
        }
    
    } while (choice != 10);
    
    return 0;

}
