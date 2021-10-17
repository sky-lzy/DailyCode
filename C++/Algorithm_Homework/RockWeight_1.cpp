#include <iostream>

int MaxWeight(int *weight, int p, int q)
{
    if (q - p == 2)
        return std::max(weight[p], weight[p + 1]);
    int w1 = MaxWeight(weight, p + 1, q - 1) + std::max(weight[p], weight[q - 1]);
    int w2 = MaxWeight(weight, p, q - 2) + weight[q - 1];
    int w3 = MaxWeight(weight, p + 2, q) + weight[p];
    return w1 > w2 ? (w1 > w3 ? w1 : w3) : (w2 > w3 ? w2 : w3);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *weight = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", weight + i);

    int w = MaxWeight(weight, 0, n);
    printf("%d\n", w);
    delete[] weight;
    return 0;
}