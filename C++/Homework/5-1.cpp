#include <iostream>
#include <cstring>
using namespace std;

class Date
{
private:
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
    input >> d.year >> d.month >> d.day;
    return input;
}

ostream &operator<<(ostream &output, Date &d)
{
    output << d.year << "." << d.month << "." << d.day;
    return output;
}

class People
{
private:
    char name[11];
    char number[7];
    char sex[3];
    Date birthday;
    char id[18];

public:
    People();
    People(const char *n, const char *num, const char *s, const Date b, const char *i);
    People(const People &);
    ~People();
    friend istream &operator>>(istream &, People &);
    friend ostream &operator<<(ostream &, People &);
    inline void changeNum(const char *);
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

People::~People()
{
    cout << "欢迎使用，再见！" << endl;
}

istream &operator>>(istream &input, People &p)
{
    input >> p.name >> p.sex >> p.birthday >> p.id;
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

void People::changeNum(const char *num)
{
    strcpy(number, num);
}

int main()
{
    People p[3] = {People("Zhao", "2021001", "m", Date(2000, 1, 1), "110000200001010001")};
    cin >> p[1];
    p[2] = p[1];
    cout << p[0] << p[1] << p[2];
    return 0;
}