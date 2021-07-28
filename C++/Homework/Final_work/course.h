#ifndef COURSE_H
#define COURSE_H

#include "report.h"

class Course : public Report
{
protected:
    std::string subject;      //学科
    std::string teacher_name; //授课教师
    int credit;               //学分
    int average;              //平均分

public:
    Course();
    //构造函数，传参：学科、授课教师、学分
    Course(const std::string &s, const std::string &tn, const int c);

    //增加成绩
    virtual void add_score(const Score &inputScore);

    //计算课程平均分
    void calculate();

    void setSubject(const std::string &s) { subject = s; }
    void setTeacherName(const std::string &tn) { teacher_name = tn; }
    void setCredit(const int c) { credit = c; }

    std::string getSubject() const { return subject; }
    std::string getTeacherName() const { return teacher_name; }
    int getCredit() const { return credit; }
    int getAverage() const { return average; }

    friend std::istream &operator>>(std::istream &, Course &);
    friend std::ostream &operator<<(std::ostream &, const Course &);
};

#endif