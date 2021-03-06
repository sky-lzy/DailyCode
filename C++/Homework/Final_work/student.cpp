#include "student.h"
#include <iostream>
#include <algorithm>

int Student::student_number = 1;

Student::Student(const std::string &n, const char s, const int g, const std::string &d)
    : People(n, s), grade(g), department(d), GPA(0), total_credits(0)
{
    number = 202101000 + student_number;
    ++student_number;
}

void Student::add_score(const std::string &sub, const std::string &tn, const int s, const int c)
{
    double tem = Report::add_score(sub, name, tn, s, c);         //保存返回的课程绩点
    GPA = (total_credits * GPA + c * tem) / (total_credits + c); //计算总学分绩
    total_credits += c;                                          //计算总学分
}

void Student::print() const
{
    std::cout << "姓名：" << name << std::endl;
    std::cout << "性别：" << sex << std::endl;
    std::cout << "学号：" << number << std::endl;
    std::cout << "年级：" << grade << std::endl;
    std::cout << "院系：" << department << std::endl;

    std::cout << "所有成绩如下：" << std::endl;
    std::for_each(report.begin(), report.end(), [](const Score &s)
                  { s.print_score(); });

    std::cout << "总学分：" << total_credits << "  " << "总学分绩：" << GPA;
}