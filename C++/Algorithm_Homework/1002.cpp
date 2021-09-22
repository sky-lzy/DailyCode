#include <iostream>
using namespace std;

void Fibonacci(int n)
{
    int a = 0, b = 1;
    if (n == 0 || n == 1)
    {
        cout << n << endl;
        return;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int t = b;
        b += a;
        a = t;
        a %= 9973;
        b %= 9973;
    }
    cout << b << endl;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        t %= 2 * 9973 + 2;
        Fibonacci(t);
    }
    return 0;
}
