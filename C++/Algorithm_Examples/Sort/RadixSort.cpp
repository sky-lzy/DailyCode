/*********************************************
 * 基数排序
 * 要求: 每个元素都为 d 位数
 * 复杂度: 若 d 为常数且k = O(n)时, 复杂度为Θ(n)
 * ******************************************* */

#include <iostream>
#include <ctime>
#include <random>
using namespace std;

//以计数排序作为中间稳定排序
void CountSort(int *list, int m, int n)
{
    int *list_m = new int[n];
    int *list_10 = new int[10];
    int *list_temp = new int[n];
    for (int i = 0; i < n; i++)
    {
        list_m[i] = list[i];
        for (int j = 0; j < m - 1; j++)
            list_m[i] /= 10;
        list_m[i] %= 10;
    }
    for (int i = 0; i < 10; i++)
        list_10[i] = 0;

    for (int i = 0; i < n; i++)
        list_10[list_m[i]]++;

    for (int i = 1; i < 10; i++)
        list_10[i] += list_10[i - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        list_temp[list_10[list_m[i]] - 1] = list[i];
        list_10[list_m[i]]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = list_temp[i];

    delete[] list_m;
    delete[] list_10;
    delete[] list_temp;
}

//基数排序函数
void RadixSort(int *list, int d, int n)
{
    for (int i = 1; i <= d; i++)
        CountSort(list, i, n);
}

int main()
{
    //随机生成100个0~1000的数进行测试
    srand(time(nullptr));
    int a[100];
    for (int i = 0; i < 100; i++)
        a[i] = rand() % 1000;
    
    RadixSort(a, 3, 100);
    for (int i = 0; i < 100; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}