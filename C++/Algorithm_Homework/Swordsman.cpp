#include <iostream>
// #include <vector>

#define MAXSIZE 1000001

int value[MAXSIZE];
int MaxValue[MAXSIZE][3];
int MaxValueEnd[MAXSIZE][3];

int Calculate(int N)
{
    for (int num = 0; num < 3; num++)
    {
        MaxValue[num][num] = -0x7fffffff;
        MaxValueEnd[num][num] = 0;
        for (int k = 0; k <= num; k++)
            MaxValueEnd[num][num] += value[k];

        for (int end = num + 1; end < N; end++)
        {
            MaxValue[end][num] = std::max(MaxValue[end - 1][num], MaxValueEnd[end - 1][num]);
            if (num > 0)
                MaxValueEnd[end][num] = std::max(MaxValueEnd[end - 1][num], MaxValue[end - 1][num - 1]) + value[end];
            else
                MaxValueEnd[end][num] = std::max(MaxValueEnd[end - 1][0], 0) + value[end];
        }
    }
    return std::max(MaxValue[N - 1][2], MaxValueEnd[N - 1][2]);
}

int main()
{
    int N, max, sum = 0;
    scanf("%d", &N);
    // int value[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &value[i]);
        sum += value[i];
    }

    max = Calculate(N);

    for (int i = 0; i < N; i++)
        value[i] = -value[i];

    max = std::max(max, sum + Calculate(N));

    printf("%d\n", max);
    return 0;
}