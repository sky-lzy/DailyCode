#include <iostream>
#include <vector>
#include <queue>

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
    std::priority_queue<int, std::vector<int>, std::greater<int>> tempMax;
    for (int i = 0; i < 3; i++)
        tempMax.push(-0x7fffffff);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &value[i]);
        sum += value[i];
        if (value[i] > tempMax.top())
        {
            tempMax.pop();
            tempMax.push(value[i]);
        }
    }

    int MaxSum3 = 0;
    bool flag = false;
    while (!tempMax.empty())
    {
        MaxSum3 += tempMax.top();
        if (tempMax.top() < 0)
            flag = true;
        tempMax.pop();
    }
    
    if (flag)
    {
        printf("%d\n", MaxSum3);
        return 0;
    }
    

    max = Calculate(N);

    for (int i = 0; i < N; i++)
        value[i] = -value[i];

    max = std::max(max, sum + Calculate(N));

    printf("%d\n", max);
    return 0;
}