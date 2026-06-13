#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
    Student students[STUDENT_MAX];
    int count = 0;

    loadStudents(students, count);
    calculateAllAverages(students, count);

    int choice;

    do
    {
        cout << "\n===== STUDENT DATABASE =====\n";
        cout << "1. Display\n";
        cout << "2. Search by Course\n";
        cout << "3. Assignment Averages\n";
        cout << "4. Hardest Assignment\n";
        cout << "5. Course Enrollment\n";
        cout << "6. Sort by Averages\n";
        cout << "7. Add Student\n";
        cout << "8. At Risk Students\n";
        cout << "9. Exit\n";
        cout << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayStudents(students, count);
            break;

        case 2:
            searchByCourse(students, count);
            break;

        case 3:
            showAssignmentAverage(students, count);
            break;

        case 4:
            showHardestAssignment(students, count);
            break;

        case 5:
            courseEnrollment(students, count);
            break;

        case 6:
            sortByAverage(students, count);
            displayStudents(students, count);
            break;

        case 7:
            addStudent(students, count);
            saveStudents(students, count);
            count = 0;
            loadStudents(students, count);
            calculateAllAverages(students, count);
            displayStudents(students, count);
            break;

        case 8:
            atRiskStudents(students, count);
            break;

        case 9:
            cout << "\nExiting program..." << endl;
            break;

        default:
            cout << "\nInvalid choice!" << endl;
        }

    } while (choice != 9);
}//end of main