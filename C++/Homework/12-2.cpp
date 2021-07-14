#include <iostream>
#include <iostream>

template <typename T>
class TT
{
private:
    int n;
    T *a;

public:
    TT();
    TT(const int nn, const T *x);
    TT(const TT &);
    int search(const T &);
    ~TT();
};

template <typename T>
TT<T>::TT() : n(0), a(NULL) {}

template <typename T>
TT<T>::TT(const int nn, const T *x) : n(nn)
{
    a = new T[n];
    for (int i = 0; i < n; i++)
        a[i] = x[i];
}

template <typename T>
TT<T>::TT(const TT &x) : n(x.n)
{
    a = new T[n];
    for (int i = 0; i < n; i++)
        a[i] = x.a[i];
}

template <typename T>
int TT<T>::search(const T &x)
{
    bool flag = false;
    int re = 0;
    for (int i = 0; i < n && !flag; i++)
        if (a[i] == x)
        {
            flag = true;
            re = i + 1;
        }
    return re;
}

template <typename T>
TT<T>::~TT()
{
    delete[] a;
}

int main()
{
    std::string b[10] = {"this", "is", "a", "lovely", "baby", "hello", "world", "mother", "father", "sister"};
    TT<std::string> a{10, b};
    std::cout << "请输入你要找的单词：" << std::endl;
    std::string word;
    std::cin >> word;
    int c = a.search(word);
    if (!c)
        std::cout << "对不起，您查找的单词 " << word << " 不存在！" << std::endl;
    else
        std::cout << "单词 " << word << " 在第" << c << "个！" << std::endl;
    return 0;
}