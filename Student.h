// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int studentID;
    std::string firstName;
    std::string lastName;
    double gpa;
    int creditHours;
    std::string major;

public:
    // Constructors
    Student();
    Student(int id,
            const std::string& fName,
            const std::string& lName,
            double gpaVal,
            int hours,
            const std::string& maj);

    // Getters
    int getID() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    double getGPA() const;
    int getCreditHours() const;
    const std::string& getMajor() const;

    // Setters
    void setFirstName(const std::string& f);
    void setLastName(const std::string& l);
    void setGPA(double g);
    void setCreditHours(int c);
    void setMajor(const std::string& m);

    // Convenience: full name and CSV row
    std::string getFullName() const;
    std::string toCSVRow() const;

    // Display function (for debugging / CLI)
    void print() const;
};

#endif
