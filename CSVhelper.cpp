// CSVHelper.cpp
#include "CSVHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CSVHelper::save(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }

    file << "ID,FirstName,LastName,GPA,CreditHours,Major\n";
    for (const auto& s : students) {
        file << s.toCSVRow() << "\n";
    }
}

std::vector<Student> CSVHelper::load(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << "\n";
        return students;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line)) {
        if (isHeader) { // skip header
            isHeader = false;
            continue;
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string item;

        int id, creditHours;
        std::string fname, lname, major;
        double gpa;

        try {
            std::getline(ss, item, ',');
            id = std::stoi(item);

            std::getline(ss, fname, ',');

            std::getline(ss, lname, ',');

            std::getline(ss, item, ',');
            gpa = std::stod(item);

            std::getline(ss, item, ',');
            creditHours = std::stoi(item);

            std::getline(ss, major, ',');

            students.emplace_back(id, fname, lname, gpa, creditHours, major);
        } catch (const std::exception& e) {
            std::cerr << "Skipping malformed CSV row: " << line
                      << " (" << e.what() << ")\n";
        }
    }

    return students;
}
