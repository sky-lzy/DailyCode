/************************
 * 归并排序
 * 复杂度: Θ(n*log(2)(n))
 * 非空间原址
 * ********************** */

#include <iostream>
using namespace std;

void MergeSort(int *list, int p, int q)
{
    if (p + 1 == q)
        return;

    int r = (p + q) / 2;
    MergeSort(list, p, r);
    MergeSort(list, r, q);

    int *list_1 = new int[r - p + 1];
    int *list_2 = new int[q - r + 1];
    for (int i = 0; i < r - p; i++)
        list_1[i] = list[i + p];
    for (int i = 0; i < q - r; i++)
        list_2[i] = list[i + r];
    list_1[r - p] = 0x7fffffff;
    list_2[q - r] = 0x7fffffff;

    int n1 = 0, n2 = 0;
    for (int i = p; i < q; i++)
    {
        if (list_1[n1] < list_2[n2])
            list[i] = list_1[n1++];
        else
            list[i] = list_2[n2++];
    }
    delete[] list_1;
    delete[] list_2;
}

int main()
{
    int a[10] = {3, 2, 6, 4, 9, 7, 0, 1, 5, 8};
    MergeSort(a, 0, 10);
    for (int i : a)
        cout << i << " ";
    cout << endl;
    return 0;
}