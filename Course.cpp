#include "Course.h"

using namespace std;

void Course::setCourseInfo(const std::string& prefix,
    int number, int units) 
{
    coursePrefix = prefix;
    courseNumber = number;
    courseUnits = units;
}

std::string Course::getCoursePrefix() const 
{
    return coursePrefix;
}

int Course::getCourseNumber() const 
{
    return courseNumber;
}

int Course::getCourseUnits() const 
{
    return courseUnits;
}

bool Course::operator<(const Course& otherCourse) const
{
    if (coursePrefix != otherCourse.coursePrefix)
        return (coursePrefix < otherCourse.coursePrefix);
    if (courseNumber != otherCourse.courseNumber)
        return (courseNumber < otherCourse.courseNumber);
    return (courseUnits < otherCourse.courseUnits);
}
