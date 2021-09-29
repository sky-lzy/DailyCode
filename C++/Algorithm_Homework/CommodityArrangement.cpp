#include <stdio.h>

struct Node
{
    Node *forward;
    Node *next;

    Node() : forward(nullptr), next(nullptr){};
};

inline void swap(Node *&a, Node *&b)
{
    Node *t = a;
    a = b;
    b = t;
}

inline void swap(Node &a, Node &b)
{
    if (a.next == &b)
    {
        swap(a.forward->next, b.next->forward);
        a.next = b.next;
        b.forward = a.forward;
        a.forward = &b;
        b.next = &a;
    }
    else if (b.next == &a)
    {
        swap(b.forward->next, a.next->forward);
        b.next = a.next;
        a.forward = b.forward;
        b.forward = &a;
        a.next = &b;
    }
    else
    {
        swap(a.next->forward, b.next->forward);
        swap(a.forward->next, b.forward->next);
        swap(a.next, b.next);
        swap(a.forward, b.forward);
    }
}

int main()
{
    int N, M, K, L;
    bool reverse = false;
    scanf("%d%d%d%d", &N, &M, &K, &L);
    Node *Goods = new Node[N + 2];
    for (int i = 0; i < M + N + K + L; i++)
    {
        int temp, num, j, flag, num_a, num_b;
        scanf("%d", &temp);
        switch (temp)
        {
        case 1:
            scanf("%d%d%d", &num, &j, &flag);
            if (j == -1)
            {
                Goods[0].next = &Goods[num];
                Goods[num].forward = &Goods[0];
                Goods[N + 1].forward = &Goods[num];
                Goods[num].next = &Goods[N + 1];
            }
            else
            {
                if (flag + reverse == 1)
                {
                    Goods[num].forward = &Goods[j];
                    Goods[num].next = Goods[j].next;
                    Goods[j].next = &Goods[num];
                    Goods[num].next->forward = &Goods[num];
                }
                else
                {
                    Goods[num].next = &Goods[j];
                    Goods[num].forward = Goods[j].forward;
                    Goods[j].forward = &Goods[num];
                    Goods[num].forward->next = &Goods[num];
                }
            }
            break;
        case 0:
            scanf("%d", &num);
            Goods[num].forward->next = Goods[num].next;
            Goods[num].next->forward = Goods[num].forward;
            break;

        case -1:
            scanf("%d%d", &num_a, &num_b);
            swap(Goods[num_a], Goods[num_b]);
            break;

        case -2:
            reverse = !reverse;
            break;

        default:
            break;
        }
    }

    if (!reverse)
    {
        Node *temptr = Goods[0].next;
        while (temptr != &Goods[N + 1])
        {
            printf("%d ", temptr - &Goods[0]);
            temptr = temptr->next;
        }
    }
    else
    {
        Node *temptr = Goods[N + 1].forward;
        while (temptr != &Goods[0])
        {
            printf("%d ", temptr - &Goods[0]);
            temptr = temptr->forward;
        }
    }
    printf("-1\n");
    return 0;
}