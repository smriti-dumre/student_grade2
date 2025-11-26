// MainWindow.cpp
#include "MainWindow.h"
#include "CSVHelper.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      idEdit(new QLineEdit(this)),
      firstNameEdit(new QLineEdit(this)),
      lastNameEdit(new QLineEdit(this)),
      gpaEdit(new QLineEdit(this)),
      creditHoursEdit(new QLineEdit(this)),
      majorEdit(new QLineEdit(this)),
      table(new QTableWidget(this)) {
    setupUI();
    refreshTable();
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // Inputs grid
    QGridLayout* formLayout = new QGridLayout;
    formLayout->addWidget(new QLabel("ID:"), 0, 0);
    formLayout->addWidget(idEdit, 0, 1);

    formLayout->addWidget(new QLabel("First Name:"), 1, 0);
    formLayout->addWidget(firstNameEdit, 1, 1);

    formLayout->addWidget(new QLabel("Last Name:"), 2, 0);
    formLayout->addWidget(lastNameEdit, 2, 1);

    formLayout->addWidget(new QLabel("GPA:"), 3, 0);
    formLayout->addWidget(gpaEdit, 3, 1);

    formLayout->addWidget(new QLabel("Credit Hours:"), 4, 0);
    formLayout->addWidget(creditHoursEdit, 4, 1);

    formLayout->addWidget(new QLabel("Major:"), 5, 0);
    formLayout->addWidget(majorEdit, 5, 1);

    // Buttons row
    QPushButton* addBtn    = new QPushButton("Add", this);
    QPushButton* updateBtn = new QPushButton("Update", this);
    QPushButton* deleteBtn = new QPushButton("Delete", this);
    QPushButton* searchBtn = new QPushButton("Search", this);
    QPushButton* loadBtn   = new QPushButton("Load CSV", this);
    QPushButton* saveBtn   = new QPushButton("Save CSV", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(searchBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(loadBtn);
    buttonLayout->addWidget(saveBtn);

    // Table
    table->setColumnCount(6);
    QStringList headers;
    headers << "ID" << "First Name" << "Last Name" << "GPA" << "Credit Hours" << "Major";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(table);

    central->setLayout(mainLayout);

    // Connections
    connect(addBtn,    &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdateStudent);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchStudent);
    connect(loadBtn,   &QPushButton::clicked, this, &MainWindow::onLoadFromCSV);
    connect(saveBtn,   &QPushButton::clicked, this, &MainWindow::onSaveToCSV);

    setWindowTitle("Student Grade Management System (GUI)");
}

// Collect current form values into a Student
Student MainWindow::collectFromInputs(bool& ok) const {
    ok = false;
    bool idOk, gpaOk, crOk;

    int id = idEdit->text().toInt(&idOk);
    double gpa = gpaEdit->text().toDouble(&gpaOk);
    int creditHours = creditHoursEdit->text().toInt(&crOk);

    if (!idOk || !gpaOk || !crOk) {
        return Student();
    }

    std::string f = firstNameEdit->text().toStdString();
    std::string l = lastNameEdit->text().toStdString();
    std::string m = majorEdit->text().toStdString();

    ok = true;
    return Student(id, f, l, gpa, creditHours, m);
}

void MainWindow::fillInputsFromStudent(const Student& s) {
    idEdit->setText(QString::number(s.getID()));
    firstNameEdit->setText(QString::fromStdString(s.getFirstName()));
    lastNameEdit->setText(QString::fromStdString(s.getLastName()));
    gpaEdit->setText(QString::number(s.getGPA(), 'f', 2));
    creditHoursEdit->setText(QString::number(s.getCreditHours()));
    majorEdit->setText(QString::fromStdString(s.getMajor()));
}

void MainWindow::refreshTable() {
    auto students = tree.getAllStudentsSorted();
    table->setRowCount(static_cast<int>(students.size()));

    for (int i = 0; i < static_cast<int>(students.size()); ++i) {
        const Student& s = students[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::number(s.getID())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(s.getFirstName())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(s.getLastName())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(s.getGPA(), 'f', 2)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(s.getCreditHours())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(s.getMajor())));
    }
}

// ===== Slots =====
void MainWindow::onAddStudent() {
    bool ok;
    Student s = collectFromInputs(ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "ID, GPA, and Credit Hours must be valid numbers.");
        return;
    }
    if (tree.search(s.getID())) {
        QMessageBox::warning(this, "Duplicate ID", "A student with this ID already exists.");
        return;
    }
    tree.insert(s);
    refreshTable();
}

void MainWindow::onUpdateStudent() {
    bool ok;
    Student s = collectFromInputs(ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "ID, GPA, and Credit Hours must be valid numbers.");
        return;
    }
    if (!tree.search(s.getID())) {
        QMessageBox::warning(this, "Not Found", "No student with this ID exists.");
        return;
    }
    tree.update(s);
    refreshTable();
}

void MainWindow::onDeleteStudent() {
    bool idOk;
    int id = idEdit->text().toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Invalid ID", "Enter a valid numeric ID.");
        return;
    }
    if (!tree.search(id)) {
        QMessageBox::warning(this, "Not Found", "No student with this ID exists.");
        return;
    }
    tree.remove(id);
    refreshTable();
}

void MainWindow::onSearchStudent() {
    bool idOk;
    int id = idEdit->text().toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Invalid ID", "Enter a valid numeric ID.");
        return;
    }
    Student* s = tree.search(id);
    if (!s) {
        QMessageBox::information(this, "Search", "No student with this ID exists.");
        return;
    }
    fillInputsFromStudent(*s);
}

void MainWindow::onLoadFromCSV() {
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV", "", "CSV Files (*.csv)");
    if (filename.isEmpty()) return;

    auto students = CSVHelper::load(filename.toStdString());
    // Clear the current tree and reinsert
    tree = AVLTree(); // simple way to reset
    for (const auto& s : students) {
        tree.insert(s);
    }
    refreshTable();
}

void MainWindow::onSaveToCSV() {
    QString filename = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv)");
    if (filename.isEmpty()) return;

    auto students = tree.getAllStudentsSorted();
    CSVHelper::save(filename.toStdString(), students);

    QMessageBox::information(this, "Saved", "Students saved to CSV file.");
}
