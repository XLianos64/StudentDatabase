#include "Student.h"
#include <iostream>

using namespace std;

int main() {
    Student students[MAX_STUDENTS];
    int grades[MAX_STUDENTS][NUM_ASSIGNMENTS];
    int numStudents = 0;

    loadStudents(students, numStudents, grades);
    generateGrades(grades, numStudents);
    calculateAverages(students, grades, numStudents);

    int choice;
    do {
        cout << "\n=== Student Grade System ===\n";
        cout << "1. Display All Student Info\n";
        cout << "2. Update Assignment\n";
        cout << "3. Add Student\n";
        cout << "4. Save to File\n";
        cout << "5. Highlight Student / Assignment\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllStudentInfo(students, grades, numStudents);
            break;
        case 2:
            updateAssignment(students, grades, numStudents);
            break;
        case 3:
            addStudent(students, grades, numStudents);
            break;
        case 4:
            saveStudents(students, numStudents);
            break;
        case 5:
            highlightSearch(students, grades, numStudents);
            break;
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}