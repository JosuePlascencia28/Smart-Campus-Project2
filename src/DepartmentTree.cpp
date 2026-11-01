
#include "../include/DepartmentTree.h"
#include <fstream>


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

// display the department hierarchy
void DepartmentTree::showHierarchy() {
    if (root == nullptr) {
        cout << "No departments available." << endl;
        return;
    }

    printTree(root, 0);
}

// visit departments in preorder
void printPreorder(DepartmentNode* node) {
    if (node == nullptr) {
        return;
    }

    cout << node->name << endl;

    for (DepartmentNode* child : node->children) {
        printPreorder(child);
    }
}

// display preorder traversal
void DepartmentTree::preorder() {
    if (root == nullptr) {
        cout << "No departments available." << endl;
        return;
    }

    cout << "Preorder Traversal:" << endl;
    printPreorder(root);
}

// Load departments from a text file
void DepartmentTree::loadDepartments(string filename) {
    ifstream file(filename);
    string line;
    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected" << endl;
        return;
    }

    while (getline(file, line)) {
        lineNumber++;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t pos = line.find('|');

        if (pos == string::npos ||
            line.find('|', pos + 1) != string::npos) {
            cout << filename << " line " << lineNumber
                 << ": Invalid format." << endl;
            rejected++;
            continue;
        }

        string name = line.substr(0, pos);
        string parent = line.substr(pos + 1);

        if (name.empty() || parent.empty()) {
            cout << filename << " line " << lineNumber
                 << ": Missing information." << endl;
            rejected++;
            continue;
        }

        if (root == nullptr && parent != "NONE") {
            cout << filename << " line " << lineNumber
                 << ": Root must have NONE as parent." << endl;
            rejected++;
            continue;
        }

        if (root != nullptr && parent == "NONE") {
            cout << filename << " line " << lineNumber
                 << ": Only the root can have NONE as parent." << endl;
            rejected++;
            continue;
        }

        if (findNode(root, name) != nullptr ||
            (root != nullptr && findNode(root, parent) == nullptr)) {
            cout << filename << " line " << lineNumber
                 << ": Duplicate department or unknown parent." << endl;
            rejected++;
            continue;
        }

        addDepartment(name, parent);
        accepted++;
    }

    cout << filename << ": " << accepted
         << " accepted, " << rejected << " rejected" << endl;
}

