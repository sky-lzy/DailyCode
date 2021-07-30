#ifndef STUDENT_H
#define STUDENT_H

#include "people.h"
#include "report.h"
#include <iostream>

//Student由抽象类People及类Report继承而来
class Student : public People, public Report
{
protected:
    static int student_number; //学号，系统分配
    int grade;                 //年级
    std::string department;    //院系

    int total_credits; //总学分
    double GPA;        //平均学分绩

public:
    Student();
    //构造函数，传参：姓名、性别、年级、院系
    Student(const std::string &, const char, const int, const std::string &);

    //拷贝构造函数
    Student(const Student &copyStudent);

    //打印学生信息
    virtual void print(bool flag = false) const;

    //增加科目的成绩，传参：学科、授课教师、百分制成绩、学分
    virtual void add_score(const std::string &sub, const std::string &tn, const int s, const int c);
    virtual void add_score(const Score &inputScore);

    void setGrade(const int g) { grade = g; }
    void setDepartment(const std::string &d) { department = d; }

    int getGrade() const { return grade; }
    std::string getDepartment() const { return department; }

    friend std::istream &operator>>(std::istream &, Student &);
    friend std::ostream &operator<<(std::ostream &, const Student &);
};

#endif