#include <iostream>
#include <string>
using namespace std;

int main()
{
    char str[20];
    cout << "请输入长度小于20的字符串：" << endl;
    cin >> str;
    cin.ignore(5,'\n');
    int i;
    for (i = 0; str[i]!='\0' ; i++) {}
    cout << "共读入了" << i << "个字符" << endl;
    cout << "请输入长度小于20的字符串：" << endl;
    cin.get(str, 20, '\n');
    cin.ignore(5,'\n');
    for (i = 0; str[i]!='\0' ; i++) {}
    cout << "共读入了" << i << "个字符" << endl;
    cout << "请输入长度小于20的字符串：" << endl;
    cin.getline(str, 20, '\n');
    for (i = 0; str[i]!='\0' ; i++) {}
    cout << "共读入了" << i << "个字符" << endl;
    return 0;
}