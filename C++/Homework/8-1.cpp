#include <iostream>
#include <vector>
using namespace std;

class Date
{
protected:
    int year;
    int month;
    int day;
};

class People
{
protected:
    char name[11];
    char number[7];
    char sex[3];
    Date birthday;
    char id[18];
};

class Student : virtual public People
{
protected:
    char classNo[7];
};

class Teacher : virtual public People
{
protected:
    char principalShip[11];
    char department[21];

public:
    virtual void PAY();
};

void Teacher::PAY()
{
    cout << "教师的工资为每月30000元" << endl;
}

class Graduate : public Student
{
protected:
    char subject[21];
    char teacherAdvisor[21];
};

class TA : public Teacher, public Graduate
{
};

class Prof : public Teacher
{
public:
    virtual void PAY();
};

void Prof::PAY()
{
    cout << "教授的工资为每月50000元" << endl;
}

class FemaleProf : public Prof
{
public:
    virtual void PAY();
};

void FemaleProf::PAY()
{
    cout << "女教授的工资为每月60000元" << endl;
}

int main()
{
    vector<Teacher *> p;
    p.push_back(new (Teacher));
    p.push_back(new (Prof));
    p.push_back(new (FemaleProf));
    for (int i = 0; i < p.size(); i++)
    {
        p[i]->PAY();
        delete p[i];
    }
    return 0;
}