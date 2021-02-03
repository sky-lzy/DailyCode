#include <stdio.h>

void swap(int *a, int *b) //交换元素
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
    return;
}

int main()
{
    int a, b, x, y;
    printf("请输入两个正整数：");
    scanf("%d%d", &a, &b);
    x = a;
    y = b;
    if (a > b)
        swap(&a, &b);
    while (a) //余数不为零保持循环
    {
        b %= a; //辗转相除
        if (a > b)
            swap(&a, &b);
    }
    printf("gcd(%d,%d) = %d\n", x, y, b);
    return 0;
}