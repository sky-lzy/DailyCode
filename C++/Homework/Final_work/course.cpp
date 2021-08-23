#include "course.h"
#include <algorithm>
#include <iomanip>

Course::Course() : subject(""), teacher_name(""), credit(0), average(0) {}

Course::Course(const std::string &s, const std::string &tn, const int c) : subject(s), teacher_name(tn), credit(c), average(0) {}

void Course::calculate()
{
    int s = 0;
    std::for_each(report.begin(), report.end(), [&s](const Score &sc)
                  { s += sc.getHundredMarkScore(); });
    average = double(s) / report.size();
}

void Course::add_score(const Score &inputScore)
{
    Report::add_score(inputScore.getSubject(), inputScore.getStudentName(), inputScore.getTeacherName(), inputScore.getHundredMarkScore(), inputScore.getCredit());
    calculate();
    sortGrade();
}

bool Course::delete_score(const std::string &sub)
{
    bool flag = Report::delete_score(sub);
    calculate();
    return flag;
}

void Course::print(bool flag) const
{
    std::cout << "课程：" << subject << '\t';
    std::cout << "授课教师：" << teacher_name << '\t';
    std::cout << "学分：" << credit << '\t';
    std::cout << "平均分：" << std::fixed << std::setprecision(2) << average << std::endl;
    std::cout.unsetf(std::ios::fixed);

    if (flag)
    {
        std::cout << "所有学生成绩如下：" << std::endl;
        std::for_each(report.begin(), report.end(), [](const Score &s)
                      { s.print(); });
    }
}

void Course::sortGrade()
{
    std::sort(report.begin(), report.end(), [](const Score &sc1, const Score &sc2)
              { return sc1.getHundredMarkScore() > sc2.getHundredMarkScore(); });
}

std::istream &operator>>(std::istream &input, Course &cs)
{
    input >> cs.subject >> cs.teacher_name >> cs.credit;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Course &cs)
{
    output << "Subject: " << cs.getSubject() << std::endl;
    output << "Teacher Name: " << cs.getTeacherName() << std::endl;
    output << "Credit: " << cs.getCredit() << std::endl;
    output << "Average Score: " << std::fixed << std::setprecision(2) << cs.getAverage() << std::endl;
    output.unsetf(std::ios::fixed);

    std::for_each(cs.report.begin(), cs.report.end(), [&output](const Score &s)
                  { output << s; });
    output << std::endl;
    return output;
}