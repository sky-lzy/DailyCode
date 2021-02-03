#include <iostream>
using namespace std;

class A
{
private:
    int x, y;

public:
    A(int, int);
    friend A operator+(const A &n1, const A &n2);
    void show();
};

A::A(int a, int b) : x(a), y(b) {}

A operator+(const A &n1, const A &n2)
{
    return A(n1.x + n2.x, n1.y + n2.y);
}

void A::show()
{
    cout << "x = " << x << "  y = " << y << endl;
}

int main()
{
    A x1(3, 4), x2(7, 8);
    A x3 = x1 + x2;
    x3.show();
    return 0;
}