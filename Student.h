#ifndef STUDENT_H
#define STUDENT_H

#include <string>

const int MAX_STUDENTS = 50;
const int NUM_ASSIGNMENTS = 5;

struct Student {
    std::string firstName;
    std::string lastName;
    int ID;
    double average;
};

// Function prototypes
void loadStudents(Student students[], int& count, int grades[][NUM_ASSIGNMENTS]);
void generateGrades(int grades[][NUM_ASSIGNMENTS], int numStudents);
void calculateAverages(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents);
void displayAllStudentInfo(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents, int highlightStudent = -1, int highlightAssign = -1);
void updateAssignment(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents);
void addStudent(Student students[], int grades[][NUM_ASSIGNMENTS], int& numStudents);
void saveStudents(Student students[], int numStudents);
void highlightSearch(Student students[], int grades[][NUM_ASSIGNMENTS], int numStudents);

#endif#pragma once
