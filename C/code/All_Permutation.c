#include <stdio.h>
#include <string.h>
static int num = 0;              //定义静态计数器
void swap(char *c, int x, int y) //交换c中第x与y字符
{
    char z;
    z = *(c + x);
    *(c + x) = *(c + y);
    *(c + y) = z;
    return;
}
void f(char *c, int k, int n) //全排列函数（交换-递归法）
{
    if (k == n) //判断是否已交换完成，并输出
    {
        printf("%s\n", c);
        num++; //计数器+1
    }
    else
    {
        int i;
        for (i = k; i <= n; i++)
        {
            swap(c, k, i);  //交换i与k
            f(c, k + 1, n); //调用递归算法
            swap(c, k, i);  //恢复原状（交换i与k），准备下一次交换递归
        }
    }
    return;
}

int main()
{
    char c[10];
    printf("请输入少于10个字符 :");
    scanf("%s", c);         //读取字符
    f(c, 0, strlen(c) - 1); //调用全排列递归函数
    printf("一共得到了%d个全排列组合\n", num);
    return 0;
}