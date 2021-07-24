#ifndef TEACHER_H
#define TEACHER_H

#include "people.h"
#include <vector>

class Teacher : public People
{
protected:
    static int teacher_number;       //工号，系统分配
    std::string department;          //院系
    std::vector<std::string> course; //教授的课程

public:
    Teacher();
    //构造函数，传参：姓名、性别、院系
    Teacher(const std::string &n, const char s, const std::string &d);

    //增加教授的课程名
    void add_course(const std::string &c);
    //删去教授的课程名，返回是否成功
    bool delete_course(const std::string &c);

    //打印教师信息
    virtual void print() const;

    void setDepartment(const std::string &d) { department = d; }
    std::string getDepartment() const { return department; }

    friend std::istream &operator>>(std::istream &, Teacher &);
    friend std::ostream &operator<<(std::ostream &, const Teacher &);
};

#endif