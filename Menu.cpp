// Menu.cpp
#include "Menu.h"
#include "CSVHelper.h"
#include <iostream>
#include <limits>

Menu::Menu() {}

// ===================== Display Menu =====================
void Menu::displayMenu() {
    std::cout << "\n==============================\n";
    std::cout << "  Student Grade Management System\n";
    std::cout << "==============================\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. Search Student\n";
    std::cout << "3. Update Student\n";
    std::cout << "4. Remove Student\n";
    std::cout << "5. Display All Students (Sorted)\n";
    std::cout << "6. Save to File\n";
    std::cout << "7. Load from File\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
}

// ===================== Add Student =====================
void Menu::addStudent() {
    int id, creditHours;
    double gpa;
    std::string fname, lname, major;

    std::cout << "Enter Student ID: ";
    std::cin >> id;

    std::cout << "Enter First Name: ";
    std::cin >> fname;

    std::cout << "Enter Last Name: ";
    std::cin >> lname;

    std::cout << "Enter GPA: ";
    std::cin >> gpa;

    std::cout << "Enter Credit Hours: ";
    std::cin >> creditHours;

    std::cout << "Enter Major: ";
    std::cin >> major;

    Student s(id, fname, lname, gpa, creditHours, major);
    tree.insert(s);

    std::cout << "Student added successfully!\n";
}

// ===================== Search Student =====================
void Menu::searchStudent() {
    int id;
    std::cout << "Enter Student ID to search: ";
    std::cin >> id;

    Student* result = tree.search(id);
    if (result == nullptr) {
        std::cout << "Student not found.\n";
    }
    else {
        result->print();
    }
}

// ===================== Update Student =====================
void Menu::updateStudent() {
    int id;
    std::cout << "Enter ID of student to update: ";
    std::cin >> id;

    Student* found = tree.search(id);
    if (!found) {
        std::cout << "Student not found.\n";
        return;
    }

    double gpa;
    int creditHours;
    std::string fname, lname, major;

    std::cout << "Enter new First Name: ";
    std::cin >> fname;

    std::cout << "Enter new Last Name: ";
    std::cin >> lname;

    std::cout << "Enter new GPA: ";
    std::cin >> gpa;

    std::cout << "Enter new Credit Hours: ";
    std::cin >> creditHours;

    std::cout << "Enter new Major: ";
    std::cin >> major;

    Student updated(id, fname, lname, gpa, creditHours, major);
    tree.update(updated);

    std::cout << "Student updated successfully!\n";
}

// ===================== Remove Student =====================
void Menu::removeStudent() {
    int id;
    std::cout << "Enter ID of student to remove: ";
    std::cin >> id;

    tree.remove(id);
    std::cout << "Student removed (if ID existed).\n";
}

// ===================== Display All Students =====================
void Menu::displayAllStudents() {
    std::vector<Student> list = tree.getAllStudentsSorted();

    if (list.empty()) {
        std::cout << "No students in system.\n";
        return;
    }

    for (const Student& s : list) {
        std::cout << "------------------------\n";
        s.print();
    }
}

// ===================== Save to File =====================
void Menu::saveToFile() {
    std::string filename;
    std::cout << "Enter filename to save (example: students.csv): ";
    std::cin >> filename;

    CSVHelper::save(filename, tree.getAllStudentsSorted());
    std::cout << "File saved.\n";
}

// ===================== Load from File =====================
void Menu::loadFromFile() {
    std::string filename;
    std::cout << "Enter filename to load: ";
    std::cin >> filename;

    std::vector<Student> loaded = CSVHelper::load(filename);

    // Reload tree completely
    for (const Student& s : loaded) {
        tree.insert(s);
    }

    std::cout << "File loaded and tree rebuilt.\n";
}

// ===================== Run the Main Loop =====================
void Menu::run() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: addStudent(); break;
        case 2: searchStudent(); break;
        case 3: updateStudent(); break;
        case 4: removeStudent(); break;
        case 5: displayAllStudents(); break;
        case 6: saveToFile(); break;
        case 7: loadFromFile(); break;
        case 8:
            std::cout << "Goodbye!\n";
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}
