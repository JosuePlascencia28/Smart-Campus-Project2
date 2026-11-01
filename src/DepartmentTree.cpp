
#include "../include/DepartmentTree.h"

// Find a department in the tree
DepartmentNode* findNode(DepartmentNode* node, string name) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->name == name) {
        return node;
    }

    for (DepartmentNode* child : node->children) {
        DepartmentNode* found = findNode(child, name);

        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}

// Add a department to the tree
void DepartmentTree::addDepartment(string name, string parent) {
    if (findNode(root, name) != nullptr) {
        cout << "Department already exists." << endl;
        return;
    }

    DepartmentNode* newNode = new DepartmentNode;
    newNode->name = name;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    DepartmentNode* parentNode = findNode(root, parent);

    if (parentNode == nullptr) {
        cout << "Parent department not found." << endl;
        delete newNode;
        return;
    }

    parentNode->children.push_back(newNode);
}

// search for a department and display its information
void DepartmentTree::searchDepartment(string name) {
    DepartmentNode* node = findNode(root, name);

    if (node == nullptr) {
        cout << "Department not found: " << name << endl;
        return;
    }

    cout << "Department: " << node->name << endl;
    cout << "Direct children: " << node->children.size() << endl;
}

// Display departments with indentation
void printTree(DepartmentNode* node, int depth) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    cout << node->name << endl;

    for (DepartmentNode* child : node->children) {
        printTree(child, depth + 1);
    }
}

// Display the department hierarchy
void DepartmentTree::showHierarchy() {
    if (root == nullptr) {
        cout << "No departments available." << endl;
        return;
    }

    printTree(root, 0);
}

