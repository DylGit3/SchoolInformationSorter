#include "StudentList.h"

#include <iostream>
#include <iomanip>

using namespace std;

StudentList::StudentList(const StudentList& otherStudentList)
{
    first = nullptr;
    last = nullptr;
    count = 0;

    Node* current = otherStudentList.first;
    while (current != nullptr)
    {
        addStudent(current->getStudent());
        current = current->getNext();
    }
    count = otherStudentList.count;
}

StudentList& StudentList::operator=(const StudentList& rightSide) 
{
    if (&rightSide == this)
        cerr << "Attempted assignment to itself" << "\n";
    else if (rightSide.count == 0)
        clearStudentList();
    else if (count == 0)
        copyCallingObjIsEmpty(rightSide);
    else if (count == rightSide.count)
        copyObjectsSameLength(rightSide);
    return *this;
}

void StudentList::copyCallingObjIsEmpty(const StudentList& otherStudentList)
{
    Node* current = otherStudentList.first;
    for (int i = 0; i < otherStudentList.count; ++i)
    {
        addStudent(current->getStudent());
        current = current->getNext();
    }
}

void StudentList::copyObjectsSameLength(const StudentList& otherStudentList)
{
    Node* current = first;
    Node* studentToCopy = otherStudentList.first;
    while (current != nullptr)
    {
        current->setStudent(studentToCopy->getStudent());
        current = current->getNext();
        studentToCopy = studentToCopy->getNext();
    }
}

void StudentList::copyCallingObjLonger(const StudentList& otherStudentList)
{
    Node* current = first;
    Node* previous = nullptr;
    Node* studentToCopy = otherStudentList.first;

    while (studentToCopy != nullptr) 
    {
        current->setStudent(studentToCopy->getStudent());
        previous = current;
        current = current->getNext();
        studentToCopy = studentToCopy->getNext();
    }

    if (previous != nullptr) 
    {
        previous->setNext(nullptr);
    }
    while (current != nullptr) 
    {
        Node* toDelete = current;
        current = current->getNext();
        delete toDelete;
    }
}

void StudentList::copyCallingObjShorter(const StudentList& otherStudentList)
{
    Node* current = first;
    Node* studentToCopy = otherStudentList.first;

    while (current != nullptr) 
    {
        current->setStudent(studentToCopy->getStudent());
        current = current->getNext();
        studentToCopy = studentToCopy->getNext();
    }

    while (studentToCopy != nullptr)
    {
        addStudent(studentToCopy->getStudent());
        studentToCopy = studentToCopy->getNext();
    }
}
