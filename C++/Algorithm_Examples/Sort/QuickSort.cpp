/***************************
 * 快速排序
 * (最大)复杂度: Θ(n^2)
 * 期望复杂度: Θ(n*log(2)(n))
 * 特点: 常数因子小、常用算法
 * 空间原址
 * ************************* */

#include <iostream>
using namespace std;

//数组划分函数; 复杂度: Θ(n)
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

//随机划分函数; 防止特定的输入导致复杂度较大
int RandomPartition(int *list, int p, int q)
{
    int i = p + rand() % (q - p);
    int t = list[i];
    list[i] = list[q - 1];
    list[q - 1] = t;
    return Partition(list, p, q);
}

//快速排序函数
void QuickSort(int *list, int p, int q)
{
    if (p + 1 >= q)
        return;
    int r = RandomPartition(list, p, q);
    QuickSort(list, p, r);
    QuickSort(list, r + 1, q);
}

int main()
{
    int a[10] = {3, 2, 6, 4, 9, 7, 0, 1, 8, 5};
    QuickSort(a, 0, 10);
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}