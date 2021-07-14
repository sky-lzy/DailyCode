#include "6-2.h"
#include <vector>

class Student : virtual public People
{
protected:
    char classNo[7];

public:
    Student();
    Student(const Student &);
    Student(const char *n, const char *num, const char *s, const Date b, const char *i, const char *c);
    void show();
    void input();
};

Student::Student() {}

Student::Student(const Student &s) : People(s)
{
    strcpy(classNo, s.classNo);
}

Student::Student(const char *n, const char *num, const char *s, const Date b, const char *i, const char *c) : People(n, num, s, b, i)
{
    strcpy(classNo, c);
}

void Student::show()
{
    cout << *this;
    cout << "classNo：" << classNo << endl;
}

void Student::input()
{
    cin >> *this;
    cout << "classNo：" << endl;
    cin >> classNo;
}

class Teacher : virtual public People
{
protected:
    char principalShip[11];
    char department[21];

public:
    Teacher();
    Teacher(const Teacher &);
    Teacher(const char *n, const char *num, const char *s, const Date b, const char *i, const char *p, const char *d);
    void show();
    void input();
};

Teacher::Teacher() {}

Teacher::Teacher(const Teacher &t) : People(t)
{
    strcpy(principalShip, t.principalShip);
    strcpy(department, t.department);
}

Teacher::Teacher(const char *n, const char *num, const char *s, const Date b, const char *i, const char *p, const char *d) : People(n, num, s, b, i)
{
    strcpy(principalShip, p);
    strcpy(department, d);
}

void Teacher::show()
{
    cout << *this;
    cout << "principalship：" << principalShip << endl;
    cout << "department：" << department << endl;
}

void Teacher::input()
{
    cin >> *this;
    cout << "principalship：" << endl;
    cin >> principalShip;
    cout << "department：" << endl;
    cin >> department;
}

class Graduate : public Student
{
protected:
    char subject[21];
    char teacherAdvisor[21];

public:
    Graduate();
    Graduate(const Graduate &);
    Graduate(const char *n, const char *num, const char *s, const Date b, const char *i, const char *c, const char *sub, const char *t);
    void show();
    void input();
};

Graduate::Graduate() {}

Graduate::Graduate(const Graduate &g) : People(g), Student(g)
{
    strcpy(subject, g.subject);
    strcpy(teacherAdvisor, g.teacherAdvisor);
}

Graduate::Graduate(const char *n, const char *num, const char *s, const Date b, const char *i, const char *c, const char *sub, const char *t) : People(n, num, s, b, i), Student(n, num, s, b, i, c)
{
    strcpy(subject, sub);
    strcpy(teacherAdvisor, t);
}

void Graduate::show()
{
    Student::show();
    cout << "subject：" << subject << endl;
    cout << "teacherAdvisor：" << teacherAdvisor << endl;
}

void Graduate::input()
{
    Student::input();
    cout << "subject：" << endl;
    cin >> subject;
    cout << "teacherAdvisor" << endl;
    cin >> teacherAdvisor;
}

class TA : public Teacher, public Graduate
{
public:
    TA();
    TA(const TA &);
    TA(const char *n, const char *num, const char *s, const Date b, const char *i, const char *p, const char *d, const char *c, const char *sub, const char *t);
    void show();
    void input();
};

TA::TA() {}

TA::TA(const TA &t) : Teacher(t), Graduate(t) {}

TA::TA(const char *n, const char *num, const char *s, const Date b, const char *i, const char *p, const char *d, const char *c, const char *sub, const char *t) : People(n, num, s, b, i), Teacher(n, num, s, b, i, p, d), Graduate(n, num, s, b, i, c, sub, t) {}

void TA::show()
{
    Teacher::show();
    cout << "classNo：" << classNo << endl;
    cout << "subject：" << subject << endl;
    cout << "teacherAdvisor：" << teacherAdvisor << endl;
}

void TA::input()
{
    Teacher::input();
    cout << "classNo：" << endl;
    cin >> classNo;
    cout << "subject：" << endl;
    cin >> subject;
    cout << "teacherAdvisor" << endl;
    cin >> teacherAdvisor;
}

int main()
{
    vector<Date> d; //构建日期数组
    d.push_back(Date(1980, 1, 1));
    d.push_back(Date(1990, 1, 5));
    d.push_back(Date(1995, 1, 10));
    d.push_back(Date(2000, 2, 1));
    vector<Student> s;                                                        //构建学生数组
    s.push_back(Student("Zhao", "1", "m", d[3], "110000200002010001", "01")); //实现加入
    s.push_back(Student("Qian", "2", "m", d[3], "210000200002010003", "02"));
    s.push_back(Student("Sun", "3", "f", d[3], "310000200002010004", "03"));
    cout << "Student 3：" << endl;
    s[2].show();       //实现输出
    s.pop_back();      //实现删除
    vector<Teacher> t; //构建教师数组
    t.push_back(Teacher("Li", "4", "m", d[0], "110000198001010007", "professor", "math"));
    t.push_back(Teacher("Zhou", "5", "m", d[0], "220000198001010009", "professor", "physics"));
    t.push_back(Teacher("Wu", "6", "f", d[0], "330000198001010006", "professor", "chemistry"));
    t.push_back(Teacher("Zheng", "7", "m", d[0], "440000198001010011", "professor", "biology"));
    cout << "Teacher 2：" << endl;
    t[1].show();
    cout << "Please input the message of teacher 3" << endl;
    t[2].input(); //实现输入
    t.pop_back(); //实现删除
    t.pop_back();
    vector<Graduate> g; //构建研究生数组
    g.push_back(Graduate("Wang", "8", "f", d[2], "110000199501100002", "04", "astronomy", "Feng"));
    g[0].show();
    g.pop_back();
    vector<TA> ta;
    ta.push_back(TA("Chen", "9", "f", d[1], "220000199001050004", "Ta", "physics", "05", "phsics", "Chu"));
    ta[0].show();
    ta.pop_back();
    return 0;
}