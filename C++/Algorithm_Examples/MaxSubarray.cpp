//使用分治算法求最大子列
//可以进一步输出子列

#include <iostream>
using namespace std;

//三个数取最大值
int Max(int a, int b, int c)
{
    if (a > b && a > c)
        return a;
    else if (b > a && b > c)
        return b;
    else
        return c;
}

//含中间元素的最大子列
int MaxCross(int *list, int p, int q)
{
    int mid = (p + q) / 2; //取中间数
    int sum = 0, sum_left = 0, sum_right = 0;
    for (int i = mid - 1; i >= p; i--) //左侧最大值
    {
        sum += list[i];
        if (sum > sum_left)
            sum_left = sum;
    }
    sum = 0;
    for (int i = mid + 1; i < q; i++) //右侧最大值
    {
        sum += list[i];
        if (sum > sum_right)
            sum_right = sum;
    }
    sum = sum_left + sum_right + list[mid];
    return sum;
}

//最大子列(返回子列和)
int MaxSubarray(int *list, int p, int q)
{
    if (q - p == 1)
    {
        return list[p];
    }
    else
    {
        int mid = (p + q) / 2;
        int max_left = MaxSubarray(list, p, mid);
        int max_right = MaxSubarray(list, mid, q);
        int max_cross = MaxCross(list, p, q);
        return Max(max_left, max_right, max_cross); //返回三者较大
    }
}

int main()
{
    int a[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    cout << "Max Sum = " << MaxSubarray(a, 0, 16) << endl;
    return 0;
}