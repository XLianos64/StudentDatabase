#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Student.h"
using namespace std;

void loadStudents(StudentNode*& head)
{
    ifstream file("Students90.txt");

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    Student tempStudent;

    while (file >> tempStudent.firstName
        >> tempStudent.lastName
        >> tempStudent.id)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            file >> tempStudent.assignments[j];

        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++)
            file >> tempStudent.courses[j];

        StudentNode* newNode = new StudentNode();
        newNode->data = tempStudent;
        newNode->next = head;
        head = newNode;
    }

    file.close();
}

void displayStudents(StudentNode* head)
{
    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << setw(6) << ("A" + to_string(j + 1));

    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << setw(6) << current->data.assignments[j];

        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++)
            cout << setw(10) << current->data.courses[j];

        cout << endl;

        current = current->next;
    }
}

void calculateAverage(Student* s)
{
    double sum = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        sum += s->assignments[i];

    s->average = sum / NUM_ASSIGNMENTS;
}

void calculateAllAverages(StudentNode* head)
{
    StudentNode* current = head;

    while (current != nullptr)
    {
        calculateAverage(&current->data);
        current = current->next;
    }
}

void searchByCourse(StudentNode* head)
{
    string course;
    cout << "\nEnter Course: ";
    cin >> course;

    StudentNode* current = head;

    while (current != nullptr)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (current->data.courses[j] == course)
            {
                cout << current->data.id << " "
                    << current->data.firstName << " "
                    << current->data.lastName << endl;
                break;
            }
        }

        current = current->next;
    }
}

void showAssignmentAverage(StudentNode* head)
{
    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        double sum = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            sum += current->data.assignments[j];
            count++;
            current = current->next;
        }

        cout << "A" << j + 1 << ": " << sum / count << endl;
    }
}

void showHardestAssignment(StudentNode* head)
{
    double lowestAverage = 100;
    int hardestAssignment = 0;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        double sum = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            sum += current->data.assignments[j];
            count++;
            current = current->next;
        }

        double average = sum / count;

        if (average < lowestAverage)
        {
            lowestAverage = average;
            hardestAssignment = j + 1;
        }
    }

    cout << "Hardest Assignment: A" << hardestAssignment
        << " (" << lowestAverage << ")" << endl;
}

void courseEnrollment(StudentNode* head)
{
    string courseList[6] = { "COMP220", "MATH102", "STAT110", "ENGL150", "HIST210", "BIOL120" };

    for (int c = 0; c < 6; c++)
    {
        int total = 0;
        StudentNode* current = head;

        while (current != nullptr)
        {
            for (int j = 0; j < NUM_COURSES; j++)
            {
                if (current->data.courses[j] == courseList[c])
                    total++;
            }

            current = current->next;
        }

        cout << courseList[c] << ": " << total << endl;
    }
}

void sortByAverage(StudentNode* head)
{
    for (StudentNode* i = head; i != nullptr; i = i->next)
    {
        for (StudentNode* j = i->next; j != nullptr; j = j->next)
        {
            if (i->data.average < j->data.average)
            {
                Student temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void addStudent(StudentNode*& head)
{
    StudentNode* newNode = new StudentNode();

    cout << "Enter First Name: ";
    cin >> newNode->data.firstName;

    cout << "Enter Last Name: ";
    cin >> newNode->data.lastName;

    cout << "Enter ID: ";
    cin >> newNode->data.id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter A" << i + 1 << " mark: ";
        cin >> newNode->data.assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course " << i + 1 << ": ";
        cin >> newNode->data.courses[i];
    }

    calculateAverage(&newNode->data);

    newNode->next = head;
    head = newNode;
}

void atRiskStudents(StudentNode* head)
{
    StudentNode* current = head;

    while (current != nullptr)
    {
        bool hasBelow50 = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (current->data.assignments[j] < 50)
                hasBelow50 = true;
        }

        if (hasBelow50 && current->data.average >= 50 && current->data.average <= 59)
        {
            cout << current->data.id << " "
                << current->data.firstName << " "
                << current->data.lastName << " Avg: "
                << current->data.average << endl;
        }

        current = current->next;
    }
}

void saveStudents(StudentNode* head)
{
    ofstream outFile("Students90.txt");

    StudentNode* current = head;

    while (current != nullptr)
    {
        outFile << current->data.firstName << " "
            << current->data.lastName << " "
            << current->data.id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            outFile << current->data.assignments[j] << " ";

        outFile << current->data.average << " ";

        for (int j = 0; j < NUM_COURSES; j++)
            outFile << current->data.courses[j] << " ";

        outFile << endl;

        current = current->next;
    }

    outFile.close();
}

void deleteList(StudentNode*& head)
{
    while (head != nullptr)
    {
        StudentNode* temp = head;
        head = head->next;
        delete temp;
    }
}