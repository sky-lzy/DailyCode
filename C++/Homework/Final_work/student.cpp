#include "student.h"
#include <iomanip>
#include <algorithm>

int Student::student_number = 1;

Student::Student() : People(), grade(0), department(""), GPA(0), total_credits(0)
{
    number = 202101000 + student_number;
    ++student_number;
}

Student::Student(const std::string &n, const char s, const int g, const std::string &d)
    : People(n, s), grade(g), department(d), GPA(0), total_credits(0)
{
    number = 202101000 + student_number;
    ++student_number;
}

Student::Student(const Student &copyStudent)
    : People(copyStudent.name, copyStudent.sex), grade(copyStudent.grade), department(copyStudent.department), GPA(copyStudent.GPA), total_credits(copyStudent.total_credits)
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

void Student::add_score(const Score &inputScore)
{
    add_score(inputScore.getSubject(), inputScore.getTeacherName(), inputScore.getHundredMarkScore(), inputScore.getCredit());
}

void Student::print(bool flag) const
{
    std::cout << "姓名：" << name << '\t';
    std::cout << "性别：" << sex << '\t';
    std::cout << "学号：" << number << '\t';
    std::cout << "年级：" << grade << '\t';
    std::cout << "院系：" << department << '\t';
    int numt = 2 - department.size() / 10;
    for (int i = 0; i < numt; i++)
        std::cout << '\t';

    if (flag)
    {
        std::cout << std::endl
                  << "所有成绩如下：" << std::endl;
        std::for_each(report.begin(), report.end(), [](const Score &s)
                      { s.print(); });
    }

    std::cout << "总学分：" << total_credits << '\t'
              << "总学分绩：" << std::fixed << std::setprecision(2) << GPA << std::endl;
    std::cout.unsetf(std::ios::fixed);
}

std::istream &operator>>(std::istream &input, Student &stu)
{
    input >> stu.name >> stu.sex >> stu.grade >> stu.department;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Student &stu)
{
    output << "Name: " << stu.getName() << std::endl;
    output << "Sex: " << stu.getSex() << std::endl;
    output << "Student Number: " << stu.getNumber() << std::endl;
    output << "Grade: " << stu.getGrade() << std::endl;
    output << "Department: " << stu.getDepartment() << std::endl;
    std::for_each(stu.report.begin(), stu.report.end(), [&output](const Score &s)
                  { output << s; });
    output << "Total Credits: " << stu.total_credits << '\t' << "GPA: " << std::fixed << std::setprecision(2) << stu.GPA << std::endl << std::endl;
    output.unsetf(std::ios::fixed);
    return output;
}