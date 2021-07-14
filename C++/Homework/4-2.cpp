#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
    char *str; //字符串数据

public:
    String();                         //默认构造空字符串
    String(const char *s);            //构造函数
    ~String();                        //析构函数
    String(const String &s);          //拷贝构造函数
    void show();                      //显示字符串
    bool operator==(String &s1);      //判断字符串是否相等
    bool operator>(String &s1);       //比较字符串
    bool operator<(String &s1);       //比较字符串
    String operator+(String &s1);     //字符串加和
    String operator=(String &s1);     //字符串赋值
    String operator=(const char *s1); //字符串赋值
};

String::String()
{
    str = new char[1];
    str[0] = '\0';
}

String::String(const char *s)
{
    str = new char[strlen(s) + 1];
    strcpy(str, s);
}

String::~String()
{
    delete[] str;
}

String::String(const String &s)
{
    str = new char[strlen(s.str) + 1];
    strcpy(str, s.str);
}

void String::show()
{
    cout << str << endl;
}

bool String::operator==(String &s1)
{
    bool flag = false;
    if (strcmp(str, s1.str) == 0)
        flag = true;
    return flag;
}

bool String::operator>(String &s1)
{
    bool flag = false;
    if (strcmp(str, s1.str) == 1)
        flag = true;
    return flag;
}

bool String::operator<(String &s1)
{
    bool flag = false;
    if (strcmp(str, s1.str) == -1)
        flag = true;
    return flag;
}

String String::operator+(String &s1)
{
    int s = strlen(str) + strlen(s1.str) + 1;
    char *temp = new char[s];
    strcpy(temp, str);
    strcat(temp, s1.str);
    return String(temp);
}

String String::operator=(String &s1)
{
    delete[] str;
    str = new char[strlen(s1.str)];
    strcpy(str, s1.str);
    return *this;
}

String String::operator=(const char *s1)
{
    delete[] str;
    str = new char[strlen(s1) + 1];
    strcpy(str, s1);
    return *this;
}

int main()
{
    String str[8] =
        {
            String("Alice"),
            String("Bob"),
            String("Carol"),
            String("Dave"),
            String("Eve"),
            String("Alice")};
    str[6] = "Frank";
    str[6].show();
    str[7] = str[4];
    cout << "\"Alice\" > \"Dave\" ?" << endl;
    if (str[0] > str[3])
        cout << "True!" << endl;
    else
        cout << "False!" << endl;
    String s = str[6] + str[7];
    s.show();
    return 0;
}