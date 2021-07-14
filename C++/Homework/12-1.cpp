#include <iostream>
#include <string>

template<typename T>
T* sort(T a[], const int n)
{
    for (int i = 0; i < n-1; i++)
    for (int j = i + 1; j < n; j++)
        if (a[i] > a[j])
        {
            T t;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    return a;
}

int main()
{
    std::string b[10] = {"this", "is", "a", "lovely", "baby", "hello", "world", "mother", "father", "sister"};
    std::cout << "排序之前：" << std::endl;
    for(std::string i : b)
        std::cout << i << " ";
    std::cout << std::endl;
    std::string *c = sort<std::string>(b, 10);
    std::cout << "排序之后：" << std::endl;
    for (int i = 0; i < 10; i++)
        std::cout << c[i] << " ";
    std::cout << std::endl;
    return 0;
}