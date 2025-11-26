// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QPushButton>
#include "AVLTree.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onAddStudent();
    void onDeleteStudent();
    void onSearchStudent();
    void onUpdateStudent();
    void onLoadFromCSV();
    void onSaveToCSV();

private:
    AVLTree tree;

    QLineEdit* idEdit;
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* gpaEdit;
    QLineEdit* creditHoursEdit;
    QLineEdit* majorEdit;

    QTableWidget* table;

    void setupUI();
    void refreshTable();
    Student collectFromInputs(bool& ok) const;
    void fillInputsFromStudent(const Student& s);
};

#endif
