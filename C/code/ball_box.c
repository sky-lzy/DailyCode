/*
此类问题是一类经典的问题：
    将n个球放入m个盒子中（n≥m），有多少不同的方法数？

    一共讨论八种情况：球是否相同、盒子是否相同、是否允许空盘
*/

#include <stdio.h> //经检验有问题，待调试！
#include <math.h>

int place_0(int n, int m); //函数原型声明
int place_1(int n, int m);
int place_2(int n, int m);
int place_3(int n, int m);
int place_4(int n, int m);
int place_5(int n, int m);
int place_6(int n, int m);
int place_7(int n, int m);

int factorial(int n) //阶乘函数，用来求组合数
{
    int i, s = 1;
    for (i = 1; i <= n; i++)
        s *= i;
    return s;
}

int place_0(int n, int m) //球、盒均不同，不允许空盒
{
    int s = place_2(n, m); //将 m 个盒排序种类乘盒相同的种类
    s *= factorial(m);
    return s;
}

int place_1(int n, int m) //球、盒均不同，允许空盒
{
    return (int)pow(m, n); //每一个球随意摆放即可
}

int place_2(int n, int m) //球不同、盒相同，不允许空盒
{
    int s;
    if (n == m || m == 1) //递归边界条件
        s = 1;
    else //考虑最后一个球：有一个空盒 + 没有空盒  递归
        s = place_2(n - 1, m - 1) + m * place_2(n - 1, m);
    return s;
}

int place_3(int n, int m) //球不同、盒相同，允许空盒
{
    int i, s = 0;
    for (i = 1; i <= m; i++) //将用到的盒子数量求和即可
        s += place_2(n, i);
    return s;
}

int place_4(int n, int m) //球相同、盒不同，不允许空盒
{
    int s = factorial(n - 1); //此时使用插板法，m-1 个版插 n-1 个空隙
    s /= factorial(n - m);
    s /= factorial(m - 1);
    return s;
}

int place_5(int n, int m) //球相同、盒不同，允许空盒
{
    int s = factorial(n + m - 1); //同样插板法，注意此时允许空盒  空隙为 n+m-1
    s /= factorial(n);
    s /= factorial(m - 1);
    return s;
}

int place_6(int n, int m) //球、盒均相同，不允许空盒
{
    return place_7(n - m, m); //相当于 n-m 个球放在 m 个盒中，允许空盒
}

int place_7(int n, int m) //球、盒均相同，允许空盒
{
    int s;
    if (n == 1 || m == 1) //递归边界条件
        s = 1;
    else if (n == m) //相等时考虑是否有空盒
        s = 1 + place_7(n, m - 1);
    else if (n < m) //多出的盒子不放球，直接删去
        s = place_7(n, n);
    else //每个盒子至少放一个球 + 允许有空盘
        s = place_7(n - m, m) + place_7(n, m - 1);
    return s;
}

int main()
{
    int m, n, i = 0, s;
    int (*place[8])(int n, int m) = //函数指针数组
        {
            place_0, place_1, place_2, place_3,
            place_4, place_5, place_6, place_7};
    char c;
    printf("球是否相同？（'y' or 'n'）："); //开始读取条件
    scanf("%c", &c);
    getchar(); //读空输入缓冲区
    if (c == 'y')
        i += 4;
    printf("盒子是否相同？（'y' or 'n'）：");
    scanf("%c", &c);
    getchar(); //读空输入缓冲区
    if (c == 'y')
        i += 2;
    printf("是否允许空盘？（'y' or 'n'）：");
    scanf("%c", &c);
    if (c == 'y')
        i++;
    printf("请输入球与盒的数量：");
    scanf("%d%d", &n, &m);
    s = place[i](n, m);            //按照条件调用函数
    printf("一共有%d种摆法\n", s); //输出结果
    return 0;
}