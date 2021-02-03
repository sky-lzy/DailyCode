#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Complex //定义复数类
{
private:
    double real;
    double image;

public:
    Complex(double = 0, double = 0);
    ~Complex();
    void Change(double, double); //重新赋值
    void show();
    Complex operator+(Complex &c2); //复数加法
    Complex operator-(Complex &c2); //复数减法
    Complex operator*(Complex &c2); //复数乘法
    Complex operator/(Complex &c2); //复数除法
};

Complex::Complex(double R, double I) : real(R), image(I) {}

Complex::~Complex() {}

void Complex::Change(double R, double I)
{
    real = R;
    image = I;
}

void Complex::show()
{
    cout << "<" << fixed << setprecision(2) << real << ","
         << fixed << setprecision(2) << image << "i>" << endl;
}

Complex Complex::operator+(Complex &c2)
{
    Complex c;
    c.real = real + c2.real;
    c.image = image + c2.image;
    return c;
}

Complex Complex::operator-(Complex &c2)
{
    Complex c;
    c.real = real - c2.real;
    c.image = image - c2.image;
    return c;
}

Complex Complex::operator*(Complex &c2)
{
    Complex c;
    c.real = real * c2.real - image * c2.image;
    c.image = real * c2.image + image * c2.real;
    return c;
}

Complex Complex::operator/(Complex &c2)
{
    Complex c;
    double s = real * c2.real + image * c2.image;
    c.real = (real * c2.real + image * c2.image) / s;
    c.image = (image * c2.real - real * c2.image) / s;
    return c;
}

int main()
{
    int a, b, c, d;
    cout << "请依次输入两个复数 c1 = a + bi, c2 = c + di" << endl;
    cin >> a >> b >> c >> d;
    Complex c1(a, b), c2(c, d), c3;
    cout << "c1 = ";
    c1.show();
    cout << "c2 = ";
    c2.show();
    c3 = c1 + c2;
    cout << "c1 + c2 = ";
    c3.show();
    c3 = c1 - c2;
    cout << "c1 - c2 = ";
    c3.show();
    c3 = c1 * c2;
    cout << "c1 * c2 = ";
    c3.show();
    c3 = c1 / c2;
    cout << "c1 / c2 = ";
    c3.show();
    return 0;
}