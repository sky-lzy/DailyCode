/******************************************************
 * 桶排序
 * 要求: 数据符合平均分布
 *       需要注意的是: 即使不服从均匀分布, 也可能是线性时间
 * 复杂度: 满足条件时, 期望复杂度为Θ(n)
 * 另附: 本文件使用了一定的STL简化代码量, 链表功能未具体实现
 * **************************************************** */

#include <iostream>
#include <random>
#include <memory>
#include <ctime>
#include <list>
using namespace std;

//插入排序算法, 复杂度: O(n^2)
void InsertSort(shared_ptr<list<int>> &list_p, int num)
{
    bool flag = false;
    for (list<int>::iterator list_i = list_p->begin(); list_i != list_p->end() && !flag; list_i++)
        if (num < *list_i)
        {
            list_p->insert(list_i, num);
            flag = true;
        }
    if (!flag)
        list_p->push_back(num);
}

//桶排序算法, 输入要求: n(数据个数, k(数据上限 0 ~ k))
void BucketSort(int *list_input, int n, int k)
{
    //建立10个链表存放数据
    shared_ptr<list<int>> list_temp[10];
    for (int i = 0; i < 10; i++)
        list_temp[i] = make_shared<list<int>>();
    //插入相应链表
    for (int i = 0; i < n; i++)
        InsertSort(list_temp[list_input[i] / (k / 10)], list_input[i]);
    
    //按序输出
    int temp_count = 0;
    for (int i = 0; i < 10; i++)
        for (list<int>::iterator temp_iter = list_temp[i]->begin(); temp_iter != list_temp[i]->end(); temp_iter++)
        {
            list_input[temp_count] = *temp_iter;
            temp_count++;
        }
}

int main()
{
    //随机生成100个0~1000的数进行测试
    srand(time(nullptr));
    int a[100];
    for (int i = 0; i < 100; i++)
        a[i] = rand() % 1000;
    
    BucketSort(a, 100, 1000);
    for (int i = 0; i < 100; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}