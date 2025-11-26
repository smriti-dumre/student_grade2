// Student.cpp
#include "Student.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Student::Student()
    : studentID(0),
      firstName(""),
      lastName(""),
      gpa(0.0),
      creditHours(0),
      major("") {}

Student::Student(int id,
                 const std::string& fName,
                 const std::string& lName,
                 double gpaVal,
                 int hours,
                 const std::string& maj)
    : studentID(id),
      firstName(fName),
      lastName(lName),
      gpa(gpaVal),
      creditHours(hours),
      major(maj) {}

int Student::getID() const { return studentID; }
const std::string& Student::getFirstName() const { return firstName; }
const std::string& Student::getLastName() const { return lastName; }
double Student::getGPA() const { return gpa; }
int Student::getCreditHours() const { return creditHours; }
const std::string& Student::getMajor() const { return major; }

void Student::setFirstName(const std::string& f) { firstName = f; }
void Student::setLastName(const std::string& l) { lastName = l; }
void Student::setGPA(double g) { gpa = g; }
void Student::setCreditHours(int c) { creditHours = c; }
void Student::setMajor(const std::string& m) { major = m; }

std::string Student::getFullName() const {
    return firstName + " " + lastName;
}

std::string Student::toCSVRow() const {
    std::ostringstream oss;
    oss << studentID << ","
        << firstName << ","
        << lastName << ","
        << std::fixed << std::setprecision(2) << gpa << ","
        << creditHours << ","
        << major;
    return oss.str();
}

void Student::print() const {
    std::cout << "Student ID: " << studentID << "\n"
              << "Name: " << getFullName() << "\n"
              << "GPA: " << gpa << "\n"
              << "Credit Hours: " << creditHours << "\n"
              << "Major: " << major << "\n";
}
