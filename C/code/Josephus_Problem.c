#include <stdio.h>
#include <stdlib.h>

struct people //定义结构体，存放各人编号
{
    int num;
    struct people *next;
};

int number(struct people *head, int n) //进行报数
{
    struct people *p, *q;
    int x;
    p = head;
    while (p->next != p) //循环直至最后一个人
    {
        int i;
        for (i = 1; i < n - 1; i++) //报数
            p = p->next;
        q = p->next;
        p->next = q->next; //跳过当前结点
        free(q);           //释放结点
        q = NULL;
        p = p->next; //进行下一轮报数
    }
    x = p->num; //最后一个人的编码
    free(p);
    return x;
}

int main()
{
    int m, n, i;
    struct people *p, *q, *head = NULL;
    printf("请输入总人数 m 与每一次报数 n :");
    scanf("%d%d", &m, &n);
    for (i = 1; i <= m; i++) //建立含m个人的环形链表
    {
        p = (struct people *)malloc(sizeof(struct people));
        p->num = i;
        p->next = NULL;
        if (head == NULL)
            head = p;
        else
            q->next = p;
        q = p;
    }
    q->next = head; //首尾相接
    if (n == 1)     //报数为1直接输出
        printf("最后一个人是%d\n", m);
    else if (n > 1) //进行报数
        printf("最后一个人是%d\n", number(head, n));
    else //输出错误信息
        printf("请输入正确的m与n\n");
    return 0;
}