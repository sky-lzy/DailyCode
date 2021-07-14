#include <iostream>
using namespace std;

class Student
{
private:
    int number;
    int score;
public:
    Student(int n, int s) : number(n), score(s) {}
    void getScore();
};

void Student::getScore()
{
    cout << "学号：" << number <<endl;
    cout << "成绩：" << score <<endl;
}

int main()
{
    Student stu[5] = 
    {
        Student(1,97),
        Student(2,99),
        Student(3,63),
        Student(4,81),
        Student(5,77)
    };
    Student *p = stu;
    p->getScore();
    (p+2)->getScore();
    (p+4)->getScore();
    return 0;
}