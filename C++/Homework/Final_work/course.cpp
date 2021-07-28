#include "course.h"
#include <algorithm>

Course::Course(const std::string &s, const std::string &tn, const int c) : subject(s), teacher_name(tn), credit(c) {}

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

std::istream &operator>>(std::istream &input, Course &cs)
{
    input >> cs.subject >> cs.teacher_name >> cs.credit;
    return input;
}

std::ostream &operator<<(std::ostream &output, const Course &cs)
{
    output << cs.getSubject() << cs.getTeacherName() << cs.getCredit() << cs.getAverage() << std::endl;
    std::for_each(cs.report.begin(), cs.report.end(), [&output](const Score &s)
                  { output << s; });
    return output;
}