#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// one department
struct DepartmentNode {
    string name;
    vector<DepartmentNode*> children;
};

// stores the department hierarchy
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

