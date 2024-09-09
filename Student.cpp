#include "Student.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Student::setStudent(const Student& otherStudent)
{
    studentID = otherStudent.studentID;
    firstName = otherStudent.firstName;
    lastName = otherStudent.lastName;
    numberOfCourses = otherStudent.numberOfCourses;
    tuitionWasPaid = otherStudent.tuitionWasPaid;
    coursesCompleted = otherStudent.coursesCompleted;
}

void Student::setStudentInfo(int studentIDNum, 
    const string& fName, const string& lName, bool tuitionPaid, 
    const multimap<Course, char>& coursesAndGrades)
{
    studentID = studentIDNum;
    firstName = fName;
    lastName = lName;
    tuitionWasPaid = tuitionPaid;
    coursesCompleted = coursesAndGrades;
    numberOfCourses = static_cast<int>(coursesAndGrades.size());
}

int Student::getID() const
{
    return studentID;
}

const string Student::getFirstName() const
{
    return firstName;
}

const string Student::getLastName() const
{
    return lastName;
}

void Student::getName(string& fName, string& lName) const
{
    fName = firstName;
    lName = lastName;
}

int Student::getNumberOfCourses() const
{
    return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
    int unitsCompleted = 0;
    for (const auto& course : coursesCompleted)
    {
        unitsCompleted += course.first.getCourseUnits();
    }
    return unitsCompleted;
}

multimap<Course, char> Student::getCoursesCompleted() const
{
    return coursesCompleted;
}

bool Student::isTuitionPaid() const
{
    return tuitionWasPaid;
}

bool Student::isCourseCompleted(const string& coursePrefix, 
    int courseNum) const
{
    if (coursesCompleted.empty())
        return false;
    else
    {
        for (const auto& course : coursesCompleted)
        {
            if ((course.first.getCourseNumber() == courseNum) &&
                (course.first.getCoursePrefix() == coursePrefix))
            {
                return true;
            }
        }
        return false;
    }
}

double Student::calculateGPA() const
{
    double totalPointsReceived = 0.0;
    int totalUnitsTaken = 0;
    for (const auto& studentData : coursesCompleted)
    {
        int units = studentData.first.getCourseUnits();
        char grade = studentData.second;

        double gradePoints = 0.0;
        switch (grade)
        {
        case 'A': gradePoints = 4.0; break;
        case 'B': gradePoints = 3.0; break;
        case 'C': gradePoints = 2.0; break;
        case 'D': gradePoints = 1.0; break;
        case 'F': gradePoints = 0.0;
        }

        totalPointsReceived += units * gradePoints;
        totalUnitsTaken += units;
    }
    return (totalPointsReceived / totalUnitsTaken);
}

double Student::billingAmount(double tuitionRate) const
{
    return (tuitionRate * static_cast<int>(coursesCompleted.size()));
}

void Student::printStudent() const
{
    cout << studentID << " - " << lastName << ", " << firstName << endl;
}

void Student::printStudentInfo(double tuitionRate) const
{
    cout << "\nStudent Name: " << lastName << ", " << firstName << "\n"
        << "Student ID: " << studentID << "\n"
        << "Number of courses completed: "
        << coursesCompleted.size() << "\n\n" 
        << "CourseNo  " << "Units  " << "Grade\n";
    int numOfCreditHrs = 0;
    for (const auto& courseInfo : coursesCompleted)
    {
        cout << courseInfo.first.getCoursePrefix() << " "
            << courseInfo.first.getCourseNumber() << "  "
            << "  " << courseInfo.first.getCourseUnits() << "\t "
            << "  " << courseInfo.second << "\n";
        numOfCreditHrs += courseInfo.first.getCourseUnits();
    }
    cout << "\nTotal number of credit hours: " << numOfCreditHrs << "\n";
    // Print tuition and GPA details
    if (tuitionWasPaid)
    {
        cout << "Current Term GPA: " 
            << fixed << setprecision(2) << calculateGPA() << "\n";
    }
    else
    {
        cout << "*** Grades are being held for not paying the tuition. ***\n"
            << "Amount Due: $" 
            << fixed << showpoint << setprecision(2) 
            << billingAmount(tuitionRate) << "\n";
    }

    cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
}
