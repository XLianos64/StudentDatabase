#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Student.h"

using namespace std;

void loadStudents(Student students[], int& count)
{
    ifstream inFile("Students90.txt");

    if (!inFile)
    {
        cout << "Error opening Students90.txt" << endl;
        return;
    }

    count = 0;

    while (count < STUDENT_MAX &&
        inFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id)
    {
        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            inFile >> students[count].assignments[i];
        }

        inFile >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            inFile >> students[count].courses[i];
        }

        count++;
    }

    inFile.close();
}

void calculateAverage(Student* s)
{
    double sum = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        sum += s->assignments[i];
    }

    s->average = sum / NUM_ASSIGNMENTS;
}

void calculateAllAverages(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        calculateAverage(&students[i]);
    }
}

void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

void searchByCourse(Student students[], int count)
{
    string course;

    cout << "\nEnter Course: ";
    cin >> course;

    cout << "\nStudents taking " << course << ":\n";

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << " "
                    << students[i].firstName << " "
                    << students[i].lastName << endl;
                break;
            }
        }
    }
}

void showAssignmentAverage(Student students[], int count)
{
    double sum;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        sum = 0;

        for (int i = 0; i < count; i++)
        {
            sum += students[i].assignments[j];
        }

        cout << "A" << j + 1 << ": " << sum / count << endl;
    }
}

void showHardestAssignment(Student students[], int count)
{
    double lowestAverage = 100;
    int hardestAssignment = 0;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        double sum = 0;

        for (int i = 0; i < count; i++)
        {
            sum += students[i].assignments[j];
        }

        double average = sum / count;

        if (average < lowestAverage)
        {
            lowestAverage = average;
            hardestAssignment = j + 1;
        }
    }

    cout << "Hardest Assignment: A"
        << hardestAssignment
        << " (" << lowestAverage << ")" << endl;
}

void courseEnrollment(Student students[], int count)
{
    string courseList[6] = { "COMP220", "MATH102", "STAT110", "ENGL150", "HIST210", "BIOL120" };

    for (int c = 0; c < 6; c++)
    {
        int total = 0;

        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < NUM_COURSES; j++)
            {
                if (students[i].courses[j] == courseList[c])
                {
                    total++;
                }
            }
        }

        cout << courseList[c] << ": " << total << endl;
    }
}

void sortByAverage(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (students[j].average < students[j + 1].average)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void addStudent(Student students[], int& count)
{
    if (count >= STUDENT_MAX)
    {
        cout << "Database Full!" << endl;
        return;
    }

    cout << "Enter First Name: ";
    cin >> students[count].firstName;

    cout << "Enter Last Name: ";
    cin >> students[count].lastName;

    cout << "Enter ID: ";
    cin >> students[count].id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter A" << i + 1 << " mark: ";
        cin >> students[count].assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course " << i + 1 << ": ";
        cin >> students[count].courses[i];
    }

    calculateAverage(&students[count]);

    count++;
}

void atRiskStudents(Student students[], int count)
{
    cout << "\nAt Risk Students:\n";

    for (int i = 0; i < count; i++)
    {
        bool hasBelow50 = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (students[i].assignments[j] < 50)
            {
                hasBelow50 = true;
            }
        }

        if (hasBelow50 && students[i].average >= 50 && students[i].average <= 59)
        {
            cout << students[i].id << " "
                << students[i].firstName << " "
                << students[i].lastName << " Avg: "
                << students[i].average << endl;
        }
    }
}

void saveStudents(Student students[], int count)
{
    ofstream outFile("Students90.txt");

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            outFile << students[i].assignments[j] << " ";
        }

        outFile << students[i].average << " ";

        for (int j = 0; j < NUM_COURSES; j++)
        {
            outFile << students[i].courses[j] << " ";
        }

        outFile << endl;
    }

    outFile.close();
}