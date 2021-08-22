#include "teacher.h"
#include <iostream>
#include <algorithm>

int Teacher::teacher_number = 1;

Teacher::Teacher() : People(), department("")
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

Teacher::Teacher(const Teacher &copyTeacher) : People(copyTeacher.name, copyTeacher.sex), department(copyTeacher.department)
{
    number = 202102000 + teacher_number;
    ++teacher_number;
}

void Teacher::print(bool flag) const
{
    std::cout << "姓名：" << name;
    for (int i = 0; i < 6 - name.size(); i++)
        std::cout << " ";

    std::cout << "性别：" << sex << '\t';
    std::cout << "工号：" << number << '\t';
    std::cout << "院系：" << department << std::endl;

    if (flag)
    {
        std::cout << "教授的课程：" << std::endl;
        std::for_each(course.begin(), course.end(), [](const std::string &s)
                      { std::cout << s << std::endl; });
    }
}

void Teacher::add_course(const std::string &c)
{
    if (std::find(course.begin(), course.end(), c) == course.end())
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
    output << t.getName();
    for (int i = 0; i < 8 - t.getName().size(); i++)
        output << " ";

    output << t.getSex() << '\t' << t.getNumber() << '\t' << t.getDepartment() << std::endl;
    return output;
}