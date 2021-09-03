/***********************************
 * 计数排序
 * 要求: 每个元素都是[0, k]区间内的整数
 * 复杂度: 当k = O(n), 复杂度为Θ(n)
 * ********************************* */

#include <iostream>
using namespace std;

//计数排序函数
void CountSort(int *list, int n, int k)
{
    int *list_1 = new int[k + 1];
    int *list_2 = new int[n];
    for (int i = 0; i < k + 1; i++)
        list_1[i] = 0;

    for (int i = 0; i < n; i++)
        list_1[list[i]]++;
    for (int i = 1; i < k + 1; i++)
        list_1[i] += list_1[i - 1];

    for (int i = 0; i < n; i++)
    {
        list_2[list_1[list[i]] - 1] = list[i];
        list_1[list[i]]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = list_2[i];

    delete[] list_1;
    delete[] list_2;
}

int main()
{
    int a[16] = {32, 26, 63, 47, 93, 72, 10, 15, 50, 87, 26, 72, 4, 3, 15, 50};
    CountSort(a, 16, 100);
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}