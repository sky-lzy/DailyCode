/************************
 * 堆排序
 * 复杂度: O(n*log(2)(n))
 * 空间原址
 * ********************** */
//注意: 此处输入要求heap[0] = -1为非有效信息, 有效信息范围为索引[1, n]

#include <iostream>
using namespace std;

//维护最大堆函数; 复杂度: O(log(2)(n)); 输入: 堆(数组)、结点编号、结点个数
void MaxHeapify(int *heap, int i, int n)
{
    //边界条件(是否具有子结点)
    if (i * 2 > n)
        return;

    int left = 2 * i;
    int large = heap[i] >= heap[left] ? i : left;
    //是否有另一个子结点
    if (i * 2 + 1 <= n)
    {
        int right = 2 * i + 1;
        large = heap[large] >= heap[right] ? large : right;
    }
    if (large != i)
    {
        int temp = heap[i];
        heap[i] = heap[large];
        heap[large] = temp;
        MaxHeapify(heap, large, n);
    }
}

//生成最大堆函数; 复杂度: O(n); 输入: 堆、结点个数
void BuildMaxHeap(int *heap, int n)
{
    for (int i = n / 2; i > 0; i--)
        MaxHeapify(heap, i, n);
}

//堆排序算法; 复杂度: O(n*log(2)(n))
void HeapSort(int *heap, int n)
{
    BuildMaxHeap(heap, n);
    for (int i = n; i > 1; i--)
    {
        int t = heap[1];
        heap[1] = heap[i];
        heap[i] = t;
        MaxHeapify(heap, 1, i - 1);
    }
}

int main()
{
    int a[11] = {-1, 3, 2, 6, 4, 9, 7, 0, 1, 5, 8};
    HeapSort(a, 10);
    for (int i = 1; i <= 10; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}