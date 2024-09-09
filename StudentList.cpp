#include "Course.h"
#include "StudentList.h"

#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

void StudentList::addStudent(const Student& newStudent)
{
    Node* newNode = new Node(newStudent, nullptr);

    if (first == nullptr) 
    {
        first = last = newNode;
    }
    else 
    {
        last->setNext(newNode);
        last = newNode;
    }
    count++;
}

int StudentList::getNoOfStudents() const
{
    return count;
}

void StudentList::printStudentByID(int id, double tuitionRate) const
{
    Node* current = first;
    bool hasOneOccurance = false;
    while (current != nullptr)
    {
        Student aStudent = current->getStudent();
        if (aStudent.getID() == id)
        {
            aStudent.printStudentInfo(tuitionRate);
            hasOneOccurance = true;
        }
        current = current->getNext();
    }

    if (!hasOneOccurance)
    {
        cerr << "\nNo students with ID " << id 
            << " found in the list.\n";
    }
}

void StudentList::printStudentByName(const string& name) const
{
    Node* current = first;
    bool hasOneOccurance = false;
    while (current != nullptr)
    {
        Student aStudent = current->getStudent();
        if (aStudent.getLastName() == name)
        {
            aStudent.printStudent();
            hasOneOccurance = true;
        }
        current = current->getNext();
    }

    if (!hasOneOccurance)
    {
        cerr << "No students with last name " 
            << name << " is on the list." << "\n";
    }
}

void StudentList::printStudentsByCourse(const string& coursePrefix, 
    int courseNumber) const
{
    Node* current = first;
    bool hasOneOccurance = false;
    while (current != nullptr) 
    {
        Student aStudent = current->getStudent();
        multimap<Course, char> studentCourseData = aStudent.getCoursesCompleted();

        for (const auto& courseData : studentCourseData)
        {
            if ((courseData.first.getCoursePrefix() == coursePrefix) &&
                (courseData.first.getCourseNumber() == courseNumber))
            {
                aStudent.printStudent();
                hasOneOccurance = true;
            }
        }
        current = current->getNext();
    }

    if (!hasOneOccurance)
    {
        cerr << "No students enrolled in " << coursePrefix 
            << " " << courseNumber << "." << "\n";
    }
}

void StudentList::printAllStudents(double tuitionRate) const
{
    Node* current = first;
    while (current != nullptr)
    {
        const Student aStudent = current->getStudent();

        aStudent.printStudentInfo(tuitionRate);

        current = current->getNext();
    }
}

void StudentList::clearStudentList()
{
    Node* temp = first;
    while (first != nullptr)
    {
        first = first->getNext();
        delete temp;
        temp = first;
    }
    last = nullptr;
    count = 0;
}

StudentList::~StudentList()
{
    if (first != nullptr)
    {
        clearStudentList();
    }
}

void StudentList::printStudentsToFile(ofstream& out, 
    double tuitionRate) const
{
    Node* current = first;
    while (current != nullptr)
    {
        const Student& aStudent = current->getStudent();

        out << "Student Name: " << aStudent.getLastName() << ", " 
            << aStudent.getFirstName() << "\n" 
            << "Student ID: " << aStudent.getID() << "\n" 
            << "Number of courses completed: " 
            << aStudent.getCoursesCompleted().size() << "\n\n";

        out << "CourseNo  " << "Units  " << "Grade\n";
        int numOfCreditHrs = 0;
        for (const auto& courseInfo : aStudent.getCoursesCompleted())
        {
            out << courseInfo.first.getCoursePrefix() << " " 
                << courseInfo.first.getCourseNumber() << "  "
                << "  " << courseInfo.first.getCourseUnits() << "\t " 
                << "  " << courseInfo.second << "\n";

            numOfCreditHrs += courseInfo.first.getCourseUnits();
        }
        out << "\nTotal number of credit hours: " << numOfCreditHrs << "\n";

        if (aStudent.isTuitionPaid())
        {
            out << "Current Term GPA: " << fixed 
                << setprecision(2) << aStudent.calculateGPA() << "\n";
        }
        else
        {
            out << "*** Grades are being held for not paying the tuition. ***\n"
                << "Amount Due: $" << fixed << showpoint << setprecision(2) 
                << aStudent.billingAmount(tuitionRate) << "\n";
        }

        out << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n";

        current = current->getNext();
    }
}

void StudentList::printStudentsOnHold(double tuitionRate) const {
    bool found = false;
    Node* current = first;
    while (current != nullptr) 
    {
        Student currentStudent = current->getStudent();
        if (!currentStudent.isTuitionPaid()) 
        {
            cout << currentStudent.getID() << " - " << currentStudent.getLastName() 
                << ", " << currentStudent.getFirstName() << "\n" 
                << "    Amount Due: $" << fixed << setprecision(2) 
                << currentStudent.billingAmount(tuitionRate) << "\n";
            found = true;
        }
        current = current->getNext();
    }
    if (!found) 
    {
        cout << "There are no students on hold." << "\n";
    }
}
