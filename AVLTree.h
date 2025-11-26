// AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <vector>

class AVLTree {
private:
    AVLNode* root;

    // Utility functions
    int height(AVLNode* node) const;
    int getBalance(AVLNode* node) const;

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insertNode(AVLNode* node, const Student& student);
    AVLNode* deleteNode(AVLNode* node, int studentID);
    AVLNode* minValueNode(AVLNode* node);

    AVLNode* searchNode(AVLNode* node, int studentID) const;
    void inorderTraversal(AVLNode* node, std::vector<Student>& list) const;

    void clear(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    // Public API
    void insert(const Student& student);
    void remove(int studentID);
    Student* search(int studentID);
    void update(const Student& updatedStudent);  // uses studentID as key
    std::vector<Student> getAllStudentsSorted() const;

    bool isEmpty() const { return root == nullptr; }
};

#endif
