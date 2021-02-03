#include <iostream>
using namespace std;

long long number(long long n)  //计算错排数
{
    long long s;
    if (n == 1)  //边界条件
        s = 0;
    else if (n == 2)  //边界条件
        s = 1;
    else  //递归计数：考虑错排由两种形式构成，第一个元素与其他元素交换后错排
          //或后 n - 1 个元素错排后与第一个元素交换
        s = (n - 1) * number(n - 1) + (n - 1) * number(n - 2);
    return s;
}

int main()
{
    long long n;
    cout << "请输入小于20的整数" << endl;
    cin >> n;
    if (n <= 20)
        cout << n << "个元素的错排一共有" << number(n) << "个" << endl;
    else
        cout << "请输入小于20的整数" << endl;
    return 0;
}