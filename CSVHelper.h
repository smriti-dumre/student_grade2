// CSVHelper.h
#ifndef CSVHELPER_H
#define CSVHELPER_H

#include "Student.h"
#include <vector>
#include <string>

class CSVHelper {
public:
    // Save list of students to CSV file
    static void save(const std::string& filename, const std::vector<Student>& students);

    // Load students from CSV file
    static std::vector<Student> load(const std::string& filename);
};

#endif
