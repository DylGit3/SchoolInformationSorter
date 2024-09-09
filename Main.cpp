#include "StudentList.h"
#include "OutputHandler.h"
#include "InputHandler.h"

#include <iostream>
#include <string>

using namespace std;

const string STUDENT_DATA = "student_data.txt";

void displayMenu();
void processChoice(StudentList& studentList, double tuitionRate);

int main()
{
    StudentList studentList;
    double tuitionRate = 0.0;
    readStudentData(STUDENT_DATA, studentList, tuitionRate);

    bool userInput = true;
    while (userInput)
    {
        displayMenu();
        processChoice(studentList, tuitionRate);
    }

    cout << endl;
    system("Pause");
    return 0;
}

void displayMenu()
{
    cout << "*** MAIN MENU ***\n\n"
        << "Select one of the following:\n\n"
        << "    1: Print all students\n"
        << "    2: Print student information\n"
        << "    3: Search student by last name\n"
        << "    4: Print students by course\n"
        << "    5: Print students on hold\n"
        << "    6: Print students to file\n"
        << "    7: Add new students\n"
        << "    8: To exit\n\n";
}

void processChoice(StudentList& studentList, double tuitionRate)
{
    int choice = 0;
    cout << "Enter your choice: ";
    cin >> choice;
    string name;
    int courseNumber = 0;
    string coursePrefix;
    string fName;
    string lName;
    Student newStudent;
    bool tuitionWasPaid = false;
    static int tempIDForNewStudent = 1923456;
    Course introCourse;
    introCourse.setCourseInfo("INTRO", 100, 1);
    multimap<Course, char> newStudentCourse{ {introCourse, 'A'} };

    switch (choice)
    {
    case 1:
        // Print all students
        studentList.printAllStudents(tuitionRate);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 2:
        // Print student information
        cout << "\nPlease enter student's ID: ";
        int id;
        cin >> id;
        studentList.printStudentByID(id, tuitionRate);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 3:
        // Search student by last name
        cout << "\nEnter student's last name: ";
        cin >> name;
        cout << "\n";
        studentList.printStudentByName(name);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 4:
        // Print students by course
        cout << "\nPlease enter the course prefix: ";
        cin >> coursePrefix;
        cout << "Please enter the course number: ";
        cin >> courseNumber;
        cout << "\n";
        studentList.printStudentsByCourse(coursePrefix, courseNumber);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 5:
        // Print students on hold
        cout << "\n";
        studentList.printStudentsOnHold(tuitionRate);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 6:
        printAllStudentsToFile(studentList, tuitionRate);
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 7:
        cout << "\nPlease enter first name: ";
        cin >> fName;
        cout << "Please enter last name: ";
        cin >> lName;
        newStudent.setStudentInfo(tempIDForNewStudent, fName,
            lName, tuitionWasPaid, newStudentCourse);
        studentList.addStudent(newStudent);
        ++tempIDForNewStudent;
        cout << "\n";
        system("Pause");
        cout << "\n";
        break;
    case 8:
        cout << "\nThank you for using the OCC Gradebook. Good-bye!"
            << "\n\n";
        system("Pause");
        cout << "\n";
        exit(0);
    default:
        cout << "\nSorry. That is not a selection.\n\n";
        system("Pause");
        cout << "\n";
        break;
    }
}
