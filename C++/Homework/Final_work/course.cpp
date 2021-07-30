#include "course.h"
#include <algorithm>

Course::Course() : subject(""), teacher_name(""), credit(0), average(0) {}

Course::Course(const std::string &s, const std::string &tn, const int c) : subject(s), teacher_name(tn), credit(c), average(0) {}

void Course::calculate()
{
    int n = 0, s = 0;
    std::for_each(report.begin(), report.end(), [&n, &s](const Score &sc)
                  {
                      ++n;
                      s += sc.getHundredMarkScore();
                  });
    average = s / n;
}

void Course::add_score(const Score &inputScore)
{
    Report::add_score(inputScore.getSubject(), inputScore.getStudentName(), inputScore.getTeacherName(), inputScore.getHundredMarkScore(), inputScore.getCredit());
}

void Course::print(bool flag) const
{
    std::cout << "课程：" << subject << '\t';
    std::cout << "授课教师：" << teacher_name << '\t';
    std::cout << "学分：" << credit << '\t';
    std::cout << "平均分：" << average << std::endl;

    if (flag)
    {
        std::cout << "所有学生成绩如下：" << std::endl;
        std::for_each(report.begin(), report.end(), [](const Score &s)
                      { s.print(); });
    }
}

std::istream &operator>>(std::istream &input, Course &cs)
{
    input >> cs.subject >> cs.teacher_name >> cs.credit;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Course &cs)
{
    output << cs.getSubject() << '\t' << cs.getTeacherName() << '\t' << cs.getCredit() << '\t' << cs.getAverage() << std::endl;
    std::for_each(cs.report.begin(), cs.report.end(), [&output](const Score &s)
                  { output << s; });
    return output;
}