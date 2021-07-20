#ifndef STUDENT_H
#define STUDENT_H

#include "people.h"
#include "report.h"

class Student : public People, public Report
{
protected:
    static int student_number; //学号，系统分配
    int grade;                 //年级
    std::string department;    //院系

    int total_credits; //总学分
    double GPA;        //平均学分绩

public:
    Student(const std::string &, const char, const int, const std::string &);
    virtual void print() const;
    virtual void add_score(const std::string &sub, const std::string &tn, const int s, const int c);
};

#endif