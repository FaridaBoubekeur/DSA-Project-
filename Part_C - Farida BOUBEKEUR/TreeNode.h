// farida boubekeur
// class that represents a tree node
#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include "Patient.h"

using namespace std;

class TreeNode
{
public:
    TreeNode();                // default constructor
    TreeNode(const Patient &); // parameterized constructor

    Patient *patient; // each Node data represents a patient
    TreeNode *left;
    TreeNode *right;
};

// TreeNode class functions

TreeNode::TreeNode() : left(nullptr), right(nullptr) {}

TreeNode::TreeNode(const Patient &p) : left(nullptr), right(nullptr)
{
    patient = new Patient(p);
}

#endif