#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
int main()
{
    while (1) //一直循环，直到找到不一样的数据
    {
        system(".\\data.exe > in.txt");            // data.exe运行生成数据输出到in.txt
        system(".\\std.exe < in.txt > std.txt");   // std.exe运行,从in.txt读入数据,向out.txt输出数据
        system(".\\test.exe < in.txt > test.txt"); //同上
        Sleep(1000);
        if (system("fc std.txt test.txt")) //当 fc 返回1时，说明这时数据不一样
            break;                         //不一样就跳出循环
    }
    return 0;
}