#include <iostream>
#include <fstream>
#include <strstream>
#include <vector>
#include <algorithm>
using namespace std;

struct student
{
    int num;
    string name;
    double score;
    student();
    student(const int &, const string &, const double &);
};
student::student() {}
student::student(const int &n, const string &na, const double &s) : num(n), name(na), score(s) {}

int main()
{
    vector<student> stu1;
    stu1.emplace_back(1001, "Li", 78);
    stu1.emplace_back(1002, "Wang", 89.5);
    stu1.emplace_back(1004, "Fun", 90);
    char c[50];
    ostrstream strout(c, 40);
    for_each(stu1.begin(), stu1.end(), [&strout](const student &stud) { strout << stud.num << " " << stud.name << " " << stud.score << " "; });

    vector<student> stu2;
    istrstream strin(c, 40);
    for (int i = 0; i < 3; i++)
    {
        int num2;
        string name2;
        double score2;
        strin >> num2 >> name2 >> score2;
        stu2.emplace_back(num2, name2, score2);
    }

    ofstream giveout("10-2.dat");
    for_each(stu2.begin(), stu2.end(), [&giveout](const student &stud) { giveout << stud.num << " " << stud.name << " " << stud.score << endl; });
    return 0;
}