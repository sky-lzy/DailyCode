#include <stdio.h>

inline int readNum(char *input)
{
    char temp[1000] = "";
    int i = 0;
    for (;; i++)
    {
        scanf("%c", &temp[i]);
        temp[i] -= '0';
        if (temp[i] == ' ' - '0' || temp[i] == '\n' - '0')
        {
            temp[i] = 0;
            break;
        }
    }
    int j = i - 1;
    for (int k = 0; j >= 0; j--, k++)
    {
        input[k] = temp[j];
    }
    return i - 1;
}

int main()
{
    char a[1000] = "", b[1000] = "", c[1000] = "";
    int len_a = readNum(a);
    int len_b = readNum(b);
    int len = (len_a > len_b ? len_a : len_b) + 1;
    for (int i = 0; i < 999; i++)
    {
        c[i] += a[i] + b[i];
        if (c[i] > 9)
        {
            c[i] %= 10;
            c[i + 1]++;
        }
    }
    if (c[len] == 0)
        len--;
    for (int i = len; i >= 0; i--)
    {
        printf("%d", c[i]);
    }
    printf("\n");
    return 0;
}