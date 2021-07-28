#include "student.h"
#include <algorithm>

int Student::student_number = 1;

Student::Student()
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

void Student::print() const
{
    std::cout << "姓名：" << name << std::endl;
    std::cout << "性别：" << sex << std::endl;
    std::cout << "学号：" << number << std::endl;
    std::cout << "年级：" << grade << std::endl;
    std::cout << "院系：" << department << std::endl;

    std::cout << "所有成绩如下：" << std::endl;
    std::for_each(report.begin(), report.end(), [](const Score &s)
                  { s.print(); });

    std::cout << "总学分：" << total_credits << "  "
              << "总学分绩：" << GPA;
}

std::istream &operator>>(std::istream &input, Student &stu)
{
    input >> stu.name >> stu.sex >> stu.grade >> stu.department;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Student &stu)
{
    output << stu.getName() << stu.getSex() << stu.getNumber() << stu.getGrade() << stu.getDepartment() << std::endl;
    std::for_each(stu.report.begin(), stu.report.end(), [&output](const Score &s)
                  { output << s; });
    output << stu.total_credits << stu.GPA << std::endl;
    return output;
}