#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>

//People抽象基类
class People
{
protected:
    std::string name; //姓名
    char sex;         //性别：m 男，f 女
    int number;       //编号，学生20xx01xxx，教师20xx02xxx

public:
    People() : name(""), sex('\0') {}
    People(const std::string &n, const char s) : name(n), sex(s) {}
    virtual void print(bool flag = false) const = 0;

    void setName(const std::string &n) { name = n; }
    void setSex(const char c) { sex = c; }

    std::string getName() const { return name; }
    char getSex() const { return sex; }
    int getNumber() const { return number; }
};

#endif