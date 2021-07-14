#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <fstream>
#include <strstream>
using namespace std;

//Date类的定义
class Date
{
protected:
    int year;
    int month;
    int day;

public:
    Date(int y = 0, int m = 0, int d = 0);
    Date(const char *, const char *, const char *);
    friend istream &operator>>(istream &, Date &);
    friend ostream &operator<<(ostream &, Date &);
};

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

Date::Date(const char *sy, const char *sm, const char *sd) : year(0), month(0), day(0)
{
    int k = 1;
    for (int i = strlen(sy) - 1, k = 1; i >= 0; i--)
    {
        year += (sy[i] - '0') * k;
        k *= 10;
    }
    for (int i = strlen(sm) - 1, k = 1; i >= 0; i--)
    {
        month += (sm[i] - '0') * k;
        k *= 10;
    }
    for (int i = strlen(sd) - 1, k = 1; i >= 0; i--)
    {
        day += (sd[i] - '0') * k;
        k *= 10;
    }
}

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

//People类的定义
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

//Teacher类的定义
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
    friend ofstream &operator<<(ofstream &, Teacher &);
    friend fstream &operator<<(fstream &, Teacher &);
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

ofstream &operator<<(ofstream &output, Teacher &tea)
{
    output << setiosflags(ios::left) << setw(12) << tea.name << "  "
           << setw(8) << tea.number << "  "
           << setw(4) << tea.sex << "  "
           << tea.birthday << "  "
           << setw(20) << tea.id << "  "
           << setw(12) << tea.principalShip << "  "
           << setw(22) << tea.department << endl;
    return output;
}

fstream &operator<<(fstream &output, Teacher &tea)
{
    output << setiosflags(ios::left) << setw(12) << tea.name << "  "
           << setw(8) << tea.number << "  "
           << setw(4) << tea.sex << "  "
           << tea.birthday << "  "
           << setw(20) << tea.id << "  "
           << setw(12) << tea.principalShip << "  "
           << setw(22) << tea.department << endl;
    return output;
}

//前向引用声明
string newfile();
bool modifyfile(const string &Filename, const char *number);
bool showfile(const string &Filename, const char *name);

//main函数

int main()
{
    bool flag = true;
    string FileName = "a.txt";
    while (flag)
    {
        cout << "您想要进行的操作是：\n1.创建文件并保存信息\n2.修改文件\n3.查询信息\n4.退出" << endl;
        cin.sync();
        char s = cin.get();
        char tnumber[7] = "";
        char tname[11] = "";
        try
        {
            switch (s)
            {
            case '1':
                FileName = newfile();
                break;
            case '2':
                cout << "请输入您需要修改的教师的工号" << endl;
                cin.sync();
                cin.get(tnumber, 7, '\n');
                if (!modifyfile(FileName, tnumber))
                    cout << "您查找的教师不存在，谢谢！" << endl;
                break;
            case '3':
                cout << "请输入您需要查询的教师的姓名" << endl;
                cin.sync();
                cin.get(tname, 11, '\n');
                if (!showfile(FileName, tname))
                    cout << "您查找的教师不存在，谢谢！" << endl;
                break;
            case '4':
                flag = false;
                break;
            default:
                break;
            }
        }
        catch (const int &a)
        {
            cerr << "文件打开异常！" << endl;
        }
    }
    return 0;
}

//写入信息
string newfile()
{
    string FileName;
    cout << "请输入要写入的文件名：" << endl;
    cin >> FileName;
    cin.get();
    FileName += ".txt";
    ofstream file1(FileName, ios::out);
    file1 << setiosflags(ios::left) << setw(12) << "name"
          << "  "
          << setw(8) << "number"
          << "  "
          << setw(4) << "sex"
          << "  "
          << setw(10) << "birthday"
          << "  "
          << setw(20) << "id"
          << "  "
          << setw(12) << "principalShip"
          << "  "
          << setw(22) << "department" << endl;
    bool flag = true;
    cout << "请输入老师的信息：" << endl;
    while (flag)
    {
        Teacher t0;
        t0.input();
        file1 << t0;
        cout << "是否继续输入？（请输入y or n）" << endl;
        cin.get();
        char s = cin.get();
        if (s == 'n')
            flag = false;
    }
    cin.get();
    file1.close();
    return FileName;
}

//修改文件
bool modifyfile(const string &Filename, const char *number)
{
    fstream file2(Filename, ios::in | ios::out);
    if (!file2.is_open())
        throw 1;
    bool flag = true;
    char str[101] = "";
    file2.getline(str, 150);
    auto ptr = file2.tellg();
    do
    {
        ptr = file2.tellg();
        char tnumber[7] = "";
        file2.getline(str, 150);
        for (int i = 0; str[i + 14] != ' '; i++)
        {
            tnumber[i] = str[i + 14];
        }
        if (strcmp(number, tnumber) == 0)
            flag = false;
    } while (flag && file2.peek() != EOF);
    if (flag)
        return false;
    file2.seekg(ptr);
    file2.seekp(ptr);
    cout << char(file2.peek()) << endl;

    cout << "请输入老师的信息：" << endl;
    Teacher temp;
    temp.input();
    file2 << temp;
    return true;
}

//查询信息
bool showfile(const string &Filename, const char *name)
{
    ifstream file3(Filename, ios::in);
    if (!file3.is_open())
        throw 2;
    Teacher temp;
    bool flag = true;
    char str[151] = "";
    file3.getline(str, 150);
    do
    {
        char tname[11] = "", tnumber[7] = "", tsex[3] = "", tid[19] = "", tprincipaiShip[12] = "", tdepartment[12] = "";
        char tyear[5] = "", tmonth[3] = "", tday[3] = "";
        file3.getline(str, 150);
        istrstream inp(str);
        inp.getline(tname, 11, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tnumber, 7, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tsex, 3, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tyear, 5, '.');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tmonth, 3, '.');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tday, 3, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tid, 19, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tprincipaiShip, 12, ' ');
        while (inp.peek() == ' ')
            inp.seekg(1, ios::cur);
        inp.getline(tdepartment, 12, ' ');
        if (strcmp(name, tname) == 0)
        {
            flag = false;
            temp = Teacher(tname, tnumber, tsex, {tyear, tmonth, tday}, tid, tprincipaiShip, tdepartment);
        }
    } while (flag && file3.peek() != EOF);
    if (flag)
        return false;
    temp.show();
    return true;
}