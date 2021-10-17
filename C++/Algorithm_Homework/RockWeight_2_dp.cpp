#include <iostream>

int MaxWeight(int *weight, int p, int q, int **tempResult)
{
    if (tempResult[p][q - p - 1] != 0)
        return tempResult[p][q - p - 1];

    if (q - p == 2)
        return std::max(weight[p], weight[p + 1]);

    int w1 = MaxWeight(weight, p + 1, q - 1, tempResult) + std::max(weight[p], weight[q - 1]);
    int w2 = MaxWeight(weight, p, q - 2, tempResult) + weight[q - 1];
    int w3 = MaxWeight(weight, p + 2, q, tempResult) + weight[p];
    tempResult[p][q - p - 1] = w1 > w2 ? (w1 > w3 ? w1 : w3) : (w2 > w3 ? w2 : w3);
    return tempResult[p][q - p - 1];
}

int main()
{
    int n;
    scanf("%d", &n);
    int *weight = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", weight + i);

    int **tempResult = new int *[n];
    for (int i = 0; i < n; i++)
    {
        tempResult[i] = new int[n - i];
        for (int j = 0; j < n - i; j++)
            tempResult[i][j] = 0;
    }

    int w = MaxWeight(weight, 0, n, tempResult);
    printf("%d\n", w);

    for (int i = 0; i < n; i++)
        delete[] tempResult[i];
    delete[] tempResult;
    return 0;
}