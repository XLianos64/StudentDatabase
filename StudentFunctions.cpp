#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void loadStudents(Student students[], int& count, int grades[][NUM_ASSIGNMENTS]) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Error opening students.txt!" << endl;
        return;
    }
    count = 0;
    while (count < MAX_STUDENTS && inFile >> students[count].firstName >> students[count].lastName >> students[count].ID >> students[count].average) {
        count++;
    }
    inFile.close();
    cout << "Loaded " << count << " students." << endl;
}

void generateGrades(int grades[][NUM_ASSIGNMENTS], int numStudents) {
    srand(time(0));
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            grades[i][j] = 60 + rand() % 41;  // 60-100
        }
    }
}

void calculateAverages(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        double sum = 0;
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            sum += grades[i][j];
        }
        students[i].average = sum / NUM_ASSIGNMENTS;
    }
}

void displayAllStudentInfo(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents, int highlightStudent, int highlightAssign) {
    cout << left << setw(5) << "ID" << setw(10) << "FName" << setw(10) << "LName";
    for (int j = 1; j <= NUM_ASSIGNMENTS; j++) {
        cout << setw(5) << ("A" + to_string(j));
    }
    cout << setw(8) << "AVG" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < numStudents; i++) {
        if (i == highlightStudent) cout << "\033[1;32m";  // Green row
        cout << left << setw(5) << students[i].ID << setw(10) << students[i].firstName << setw(10) << students[i].lastName;
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            if (j == highlightAssign) cout << "\033[1;33m";  // Yellow column
            cout << setw(5) << grades[i][j];
            if (j == highlightAssign) cout << "\033[0m";
        }
        cout << setw(8) << fixed << setprecision(1) << students[i].average;
        if (i == highlightStudent) cout << "\033[0m";
        cout << endl;
    }
}

void updateAssignment(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents) {
    int id, assignNum, newGrade;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter assignment number (1-5): ";
    cin >> assignNum;
    cout << "Enter new grade: ";
    cin >> newGrade;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].ID == id) {
            if (assignNum >= 1 && assignNum <= NUM_ASSIGNMENTS) {
                grades[i][assignNum - 1] = newGrade;
                calculateAverages(students, grades, numStudents);
                cout << "Grade updated successfully!" << endl;
                displayAllStudentInfo(students, grades, numStudents, -1, -1);
                return;
            }
        }
    }
    cout << "Student not found or invalid assignment!" << endl;
}

void addStudent(Student students[], int grades[][NUM_ASSIGNMENTS], int& numStudents) {
    if (numStudents >= MAX_STUDENTS) {
        cout << "Maximum students reached!" << endl;
        return;
    }
    Student newS;
    cout << "Enter first name: ";
    cin >> newS.firstName;
    cout << "Enter last name: ";
    cin >> newS.lastName;
    cout << "Enter ID: ";
    cin >> newS.ID;
    newS.average = 0.0;

    students[numStudents] = newS;
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
        grades[numStudents][j] = 60 + rand() % 41;
    }
    numStudents++;
    calculateAverages(students, grades, numStudents);
    cout << "New student added!" << endl;
}

void saveStudents(Student students[], int numStudents) {
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Error saving to file!" << endl;
        return;
    }
    for (int i = 0; i < numStudents; i++) {
        outFile << students[i].firstName << " " << students[i].lastName << " "
            << students[i].ID << " " << students[i].average << endl;
    }
    outFile.close();
    cout << "Data saved to students.txt!" << endl;
}

void highlightSearch(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents) {
    int choice;
    cout << "Highlight: 1. Student row (by ID)  2. Assignment column\nChoice: ";
    cin >> choice;
    if (choice == 1) {
        int id;
        cout << "Enter student ID: ";
        cin >> id;
        for (int i = 0; i < numStudents; i++) {
            if (students[i].ID == id) {
                displayAllStudentInfo(students, grades, numStudents, i, -1);
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    else if (choice == 2) {
        int assign;
        cout << "Enter assignment (1-5): ";
        cin >> assign;
        if (assign >= 1 && assign <= 5) {
            displayAllStudentInfo(students, grades, numStudents, -1, assign - 1);
            return;
        }
    }
    cout << "Invalid option." << endl;
}