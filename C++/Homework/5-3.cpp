#include <iostream>
using namespace std;

class Teacher
{
private:
    int num;
    string name;
    char sex;

public:
    Teacher(int n = 0, string na = "N", char s = 'm');
    ~Teacher();
    friend class Student;
    void show();
};

Teacher::Teacher(int n, string na, char s) : num(n), name(na), sex(s) {}

Teacher::~Teacher() {}

void Teacher::show()
{
    cout << "num：" << num << endl;
    cout << "name：" << name << endl;
    cout << "sex：" << sex << endl;
}

class Student
{
private:
    int num;
    string name;
    char sex;
    int grade;

public:
    Student(int n = 0, string na = "N", char s = 'm', int g = 1);
    Student(Teacher &);
    ~Student();
    void show();
};

Student::Student(int n, string na, char s, int g) : num(n), name(na), sex(s), grade(g) {}

Student::Student(Teacher &t)
{
    num = t.num;
    name = t.name;
    sex = t.sex;
    grade = 1;
}

Student::~Student() {}

void Student::show()
{
    cout << "num：" << num << endl;
    cout << "name：" << name << endl;
    cout << "sex：" << sex << endl;
    cout << "grade：" << grade << endl;
}

int main()
{
    Teacher t(50, "Liu", 'f');
    t.show();
    Student s(t);
    s.show();
    return 0;
}