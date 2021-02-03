#include <stdio.h>
#include <string.h>

void swap(char *c, int x, int y) //交换字符串中两个字符
{
    char z;
    z = *(c + x);
    *(c + x) = *(c + y);
    *(c + y) = z;
    return;
}

void arrange(char *c, int k, int n) //生成错排
{
    if (k == n) //确定最后一位时，仅存在一种错排
    {
        static int num = 0;
        printf("%s", c);
        num++;
    }
    else //分为两种情况考虑错排数：首项与其中一项交换或错排后与首项交换
    {
        int i;
        for (i = k + 1; i < n; i++)
        {
            swap(c, k, i);        //交换两字符位置
            arrange(c, k + 1, n); //后面项进行错排
            swap(c, k, i);        //还原交换，为下一次交换做准备
        }
    }
}

int main()
{
    int n;
    char c[10];
    printf("请输入少于10个字符：");
    scanf("%s", c);
    n = strlen(c);
}