#include <iostream>
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

public:
    People();
    ~People();
};

People::People()
{
    cout << "People构造函数调用！" << endl;
}

People::~People()
{
    cout << "People析构函数调用！" << endl;
}

class Student : /* virtual */ public People
{
protected:
    char classNo[7];

public:
    Student();
    ~Student();
};

Student::Student()
{
    cout << "Student构造函数调用!" << endl;
}

Student::~Student()
{
    cout << "Student析构函数调用!" << endl;
}

class Teacher : /* virtual */ public People
{
protected:
    char principalShip[11];
    char department[21];

public:
    Teacher();
    ~Teacher();
};

Teacher::Teacher()
{
    cout << "Teacher构造函数调用!" << endl;
}

Teacher::~Teacher()
{
    cout << "Teacher析构函数调用!" << endl;
}

class Graduate : public Student
{
protected:
    char subject[21];
    char teacherAdvisor[21];

public:
    Graduate();
    ~Graduate();
};

Graduate::Graduate()
{
    cout << "Graduate构造函数调用!" << endl;
}

Graduate::~Graduate()
{
    cout << "Graduate析构函数调用!" << endl;
}

class TA : public Teacher, public Graduate
{
public:
    TA();
    ~TA();
};

TA::TA()
{
    cout << "TA构造函数调用!" << endl;
}

TA::~TA()
{
    cout << "TA析构函数调用!" << endl;
}

int main()
{
    cout << "构造一个Student对象" << endl;
    Student s;
    cout << endl << "构造一个Teacher对象" << endl;
    Teacher t;
    cout << endl << "构造一个Graduate对象" << endl;
    Graduate g;
    cout << endl << "构造一个TA对象" << endl;
    TA ta;
    cout << endl;
    return 0;
}