#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    int number;
    int grade;

public:
    Student(string n, int num, int g);
    Student(const Student &p);
    int max(Student *q, int n);
    void print();
    void printNum();
};

Student::Student(string n, int num, int g) : name(n), number(num), grade(g) {}

Student::Student(const Student &p)
{
    name = p.name;
    number = p.number;
    grade = p.grade;
}

int Student::max(Student *q, int n)
{
    int m = 0;
    for (int i = 1; i < n; i++)
        if ((q + i)->grade > (q + m)->grade)
            m = i;
    return m;
}

void Student::print()
{
    cout << "姓名：" << name << endl
         << "成绩：" << grade << endl;
}

void Student::printNum()
{
    cout << "学号为：" << number << endl;
}

int main()
{
    Student stu[10] =
        {
            Student("Zhao", 1, 95),
            Student("Qian", 2, 78),
            Student("Sun", 3, 87),
            Student("Li", 4, 92),
            Student("Zhou", 5, 63),
            Student("Wu", 6, 72),
            Student("Zhen", 7, 89),
            Student("Wang", 8, 97),
            Student("Feng", 9, 69),
            Student("Chen", 10, 88)};
    int s = stu->max(stu, 10);
    cout << "分数最高的同学";
    stu[s].printNum();
    Student stu0(stu[s]);
    cout << "这名同学";
    stu0.print();
    return 0;
}