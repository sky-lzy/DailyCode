#include <iostream>
#include <cstring>
using namespace std;

class Strings
{
private:
    int length; //字符串长度
    char *str;  //字符串

public:
    Strings(const char *s);  //构造函数
    ~Strings();              //析构函数
    void Print();            //打印字符串
    void Set(const char *s); //设定字符串
};

Strings::Strings(const char *s)
{
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
}

Strings::~Strings()
{
    delete[] str;
}

void Strings::Print()
{
    cout << str << endl;
}

void Strings::Set(const char *s)
{
    delete[] str;
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
}

int main()
{
    Strings str1("Hello "), str2("");
    str2.Set("World!");
    str1.Print();
    str2.Print();
    return 0;
}