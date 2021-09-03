/****************
 * 插入排序
 * 复杂度: Θ(n^2)
 * 空间原址
 * ************** */

#include <iostream>
using namespace std;

void InsertSort(int *list, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (list[j] < list[i])
            {
                int t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
}

int main()
{
    int a[10] = {3, 2, 6, 4, 9, 7, 0, 1, 5, 8};
    InsertSort(a, 10);
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}