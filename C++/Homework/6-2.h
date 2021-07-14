#ifndef SixTwo_H
#define SixTwo_H

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Date
{
protected:
    int year;
    int month;
    int day;

public:
    Date(int y = 0, int m = 0, int d = 0);
    friend istream &operator>>(istream &, Date &);
    friend ostream &operator<<(ostream &, Date &);
};

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

istream &operator>>(istream &input, Date &d)
{
    cout << "year：" << endl;
    input >> d.year;
    cout << "month：" << endl;
    input >> d.month;
    cout << "day：" << endl;
    input >> d.day;
    return input;
}

ostream &operator<<(ostream &output, Date &d)
{
    output << setiosflags(ios::right) << setw(4) << d.year << "." << setw(2) << d.month 
    << "." << setw(2) << d.day << resetiosflags(ios::right);
    return output;
}

class People
{
protected:
    char name[11];
    char number[7];
    char sex[3];
    Date birthday;
    char id[19];

public:
    People();
    People(const char *n, const char *num, const char *s, const Date b, const char *i);
    People(const People &);
    friend istream &operator>>(istream &, People &);
    friend ostream &operator<<(ostream &, People &);
};

People::People() {}

People::People(const char *n, const char *num, const char *s, const Date b, const char *i) : birthday(b)
{
    strcpy(name, n);
    strcpy(number, num);
    strcpy(sex, s);
    strcpy(id, i);
}

People::People(const People &p)
{
    strcpy(name, p.name);
    strcpy(number, p.number);
    strcpy(sex, p.sex);
    strcpy(id, p.id);
    birthday = p.birthday;
}

istream &operator>>(istream &input, People &p)
{
    cout << "name：" << endl;
    input >> p.name;
    cout << "number：" << endl;
    input >> p.number;
    cout << "sex：" << endl;
    input >> p.sex;
    cout << "birthday：" << endl;
    input >> p.birthday;
    cout << "id：" << endl;
    input >> p.id;
    return input;
}

ostream &operator<<(ostream &output, People &p)
{
    output << "name：" << p.name << endl;
    output << "number：" << p.number << endl;
    output << "sex：" << p.sex << endl;
    output << "birthday：" << p.birthday << endl;
    output << "id：" << p.id << endl;
    return output;
}

#endif