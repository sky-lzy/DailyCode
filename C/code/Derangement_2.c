#include <stdio.h>
#include <string.h>
#include <math.h>

int check(int i, int n) //检查是否为错排
{
    int flag = 1, j, k, a[10];
    for (j = 0; j < n && flag; j++) //检查是否打乱顺序
    {
        if ((a[j] = i % n) == j)
            flag = 0;
        i /= n;
    }
    for (j = 0; j < n - 1 && flag; j++) //检查是否各出现一次
        for (k = j + 1; k < n && flag; k++)
            if (a[j] == a[k])
                flag = 0;
    return flag;
}

void out(char *c, char *x, int i, int n) //输出n元n进制下映射的原像
{
    int j;
    for (j = 0; j < n; j++)
    {
        int k = i % n;
        x[j] = c[k];
        i /= n;
    }
}

int main()
{
    char c[10] = "\0", x[10] = "\0";
    int a[10], n, i, max, num = 0;
    printf("请输入少于10个字符：");
    scanf("%s", c); //读入字符
    n = strlen(c);
    if (n >= 10)
    {
        printf("请输入少于10个字符\n");
        exit(0);
    }
    max = (int)pow(n, n);     //建立n元n进制的映射
    for (i = 0; i < max; i++) //遍历0~n^n所有情况
    {
        if (check(i, n))
        {
            out(c, x, i, n);   //生成原像
            printf("%s\n", x); //输出错排字符串
            num++;             //计数器 +1
        }
    }
    printf("共输出%d种错排\n", num);
    return 0;
}