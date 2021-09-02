/***************************
 * 快速排序
 * (最大)复杂度: Θ(n^2)
 * 期望复杂度: Θ(n*log(2)(n))
 * 特点: 常数因子小、常用算法
 * 空间原址
 * ************************* */

#include <iostream>
using namespace std;

int Partition(int *list, int p, int q)
{
    int i = p;
    for (int j = p; j < q - 1; j++)
        if (list[j] <= list[q - 1])
        {
            int t = list[i];
            list[i] = list[j];
            list[j] = t;
            i++;
        }
    int t = list[i];
    list[i] = list[q - 1];
    list[q - 1] = t;
    return i;
}

void QuickSort(int *list, int p, int q)
{
    if (p + 1 == q)
        return;
    int r = Partition(list, p, q);
    QuickSort(list, p, r - 1);
    QuickSort(list, r + 1, q);
}

int main()
{
    int a[10] = {3, 2, 6, 4, 9, 7, 0, 1, 5, 8};
    QuickSort(a, 0, 10);
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}