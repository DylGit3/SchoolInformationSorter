#ifndef STUDENTLIST_H 
#define STUDENTLIST_H 

#include <fstream>
#include <string>    

#include "Student.h" 

class Node
{
public:
    Node() : student(), next(nullptr) {}
    Node(Student newStudent, Node* newNext)
        : student(newStudent), next(newNext) {}
    Node* getNext() const { return next; }
    Student getStudent() const { return student; } 
    void setStudent(Student newStudent) { student = newStudent; }
    void setNext(Node* newNext) { next = newNext; }
    ~Node() {}
private:
    Student student;
    Node* next;
};

class StudentList
{
public:
    StudentList() : first(nullptr), last(nullptr), count(0) {}
    StudentList(const StudentList&);

    void addStudent(const Student&);

    int getNoOfStudents() const;

    void printStudentByID(int, double) const;
    void printStudentByName(const std::string&) const;
    void printStudentsByCourse(const std::string&, int) const;
    void printAllStudents(double) const;

    void clearStudentList();
    StudentList& operator=(const StudentList&);

    void printStudentsOnHold(double) const;
    void printStudentsToFile(std::ofstream& out, double tuitionRate) const;


    ~StudentList();

private:
    Node* first;
    Node* last;
    int count;

    void copyCallingObjIsEmpty(const StudentList&);
    void copyObjectsSameLength(const StudentList&);
    void copyCallingObjLonger(const StudentList&);
    void copyCallingObjShorter(const StudentList&);
};

#endif
