#include "teacher.h"
#include <iostream>
#include <algorithm>

int Teacher::teacher_number = 1;

Teacher::Teacher()
{
    number = 202102000 + teacher_number;
    ++teacher_number;
}

Teacher::Teacher(const std::string &n, const char s, const std::string &d)
    : People(n, s), department(d)
{
    number = 202102000 + teacher_number;
    ++teacher_number;
}

void Teacher::add_course(const std::string &c)
{
    course.emplace_back(c);
}

bool Teacher::delete_course(const std::string &c)
{
    bool flag = true;
    auto tem = find(course.begin(), course.end(), c);
    if (tem != course.end())
        course.erase(tem);
    else
        flag = false;
    return flag;
}

std::istream &operator>>(std::istream &input, Teacher &t)
{
    input >> t.name >> t.sex >> t.department;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Teacher &t)
{
    output << t.getName() << t.getSex() << t.getNumber() << t.getDepartment() << std::endl;
}