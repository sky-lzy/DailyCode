#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>

//People类的定义，本类为抽象基类
class People
{
protected:
    std::string name; //姓名
    char sex;         //性别：m 男，f 女
    int number;       //编号，学生以01，助教02，教师03开头

public:
    People(const std::string &n, const char s) : name(n), sex(s) {}
    virtual void print() const = 0;
};

#endif