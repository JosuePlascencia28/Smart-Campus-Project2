#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Represents one department
struct DepartmentNode {
    string name;
    vector<DepartmentNode*> children;
};

// Stores the department hierarchy
class DepartmentTree {
private:
    DepartmentNode* root = nullptr;

public:
    void addDepartment(string name, string parent);
    void searchDepartment(string name);
    void showHierarchy();
    void preorder();
    void loadDepartments(string filename);
};

