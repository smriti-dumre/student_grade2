// AVLNode.h
#ifndef AVLNODE_H
#define AVLNODE_H

#include "Student.h"

class AVLNode {
public:
    Student data;        // The student stored in this node
    AVLNode* left;       // Left child
    AVLNode* right;      // Right child
    int height;          // Height of the node for balancing

    // Constructor
    AVLNode(const Student& student)
        : data(student), left(nullptr), right(nullptr), height(1) {
    }
};

#endif

