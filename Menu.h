// Menu.h
#ifndef MENU_H
#define MENU_H

#include "AVLTree.h"
#include <string>

class Menu {
private:
    AVLTree tree;

    // Helper functions
    void addStudent();
    void searchStudent();
    void updateStudent();
    void removeStudent();
    void displayAllStudents();
    void saveToFile();
    void loadFromFile();

public:
    Menu();
    void displayMenu();
    void run();
};

#endif

