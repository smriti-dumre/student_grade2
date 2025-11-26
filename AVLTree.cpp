// AVLTree.cpp
#include "AVLTree.h"
#include <iostream>

// ===== Constructor / Destructor =====
AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}

void AVLTree::clear(AVLNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// ===== Helpers =====
int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x; // new root
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y; // new root
}

// ===== Insert =====
AVLNode* AVLTree::insertNode(AVLNode* node, const Student& student) {
    if (!node) {
        return new AVLNode(student);
    }

    if (student.getID() < node->data.getID())
        node->left = insertNode(node->left, student);
    else if (student.getID() > node->data.getID())
        node->right = insertNode(node->right, student);
    else {
        // duplicate ID – ignore or update; here we ignore insert
        return node;
    }

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Balance
    int balance = getBalance(node);

    // LL
    if (balance > 1 && student.getID() < node->left->data.getID())
        return rightRotate(node);

    // RR
    if (balance < -1 && student.getID() > node->right->data.getID())
        return leftRotate(node);

    // LR
    if (balance > 1 && student.getID() > node->left->data.getID()) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && student.getID() < node->right->data.getID()) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Student& student) {
    root = insertNode(root, student);
}

// ===== Delete =====
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

AVLNode* AVLTree::deleteNode(AVLNode* node, int studentID) {
    if (!node) return node;

    if (studentID < node->data.getID())
        node->left = deleteNode(node->left, studentID);
    else if (studentID > node->data.getID())
        node->right = deleteNode(node->right, studentID);
    else {
        // node to be deleted
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.getID());
        }
    }

    if (!node) return node;

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Rebalance
    int balance = getBalance(node);

    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::remove(int studentID) {
    root = deleteNode(root, studentID);
}

// ===== Search / Update / Traversal =====
AVLNode* AVLTree::searchNode(AVLNode* node, int studentID) const {
    if (!node) return nullptr;
    if (studentID == node->data.getID()) return node;
    if (studentID < node->data.getID())
        return searchNode(node->left, studentID);
    return searchNode(node->right, studentID);
}

Student* AVLTree::search(int studentID) {
    AVLNode* node = searchNode(root, studentID);
    return node ? &node->data : nullptr;
}

void AVLTree::update(const Student& updatedStudent) {
    AVLNode* node = searchNode(root, updatedStudent.getID());
    if (!node) return; // not found, no-op

    node->data.setFirstName(updatedStudent.getFirstName());
    node->data.setLastName(updatedStudent.getLastName());
    node->data.setGPA(updatedStudent.getGPA());
    node->data.setCreditHours(updatedStudent.getCreditHours());
    node->data.setMajor(updatedStudent.getMajor());
}

void AVLTree::inorderTraversal(AVLNode* node, std::vector<Student>& list) const {
    if (!node) return;
    inorderTraversal(node->left, list);
    list.push_back(node->data);
    inorderTraversal(node->right, list);
}

std::vector<Student> AVLTree::getAllStudentsSorted() const {
    std::vector<Student> list;
    inorderTraversal(root, list);
    return list;
}
