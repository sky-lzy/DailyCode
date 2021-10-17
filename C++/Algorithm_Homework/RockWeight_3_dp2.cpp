#include <iostream>

int main()
{
    int n;
    scanf("%d", &n);
    int *weight = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", weight + i);

    int **tempResult = new int *[2];
    tempResult[0] = new int[n];
    tempResult[1] = new int[n];
    bool flag = true;
    for (int i = 0; i < n - 1; i++)
        tempResult[0][i] = std::max(weight[i], weight[i + 1]);

    for (int i = 4; i <= n; i += 2)
    {
        for (int j = 0; j <= n - i; j++)
        {
            int w1 = tempResult[!flag][j] + weight[j + i - 1];
            int w2 = tempResult[!flag][j + 1] + std::max(weight[j], weight[j + i - 1]);
            int w3 = tempResult[!flag][j + 2] + weight[j];
            tempResult[flag][j] = w1 > w2 ? (w1 > w3 ? w1 : w3) : (w2 > w3 ? w2 : w3);
        }
        flag = !flag;
    }

    int w = tempResult[!flag][0];
    printf("%d\n", w);
    
    delete[] tempResult[0];
    delete[] tempResult[1];
    delete[] tempResult;
    return 0;
}