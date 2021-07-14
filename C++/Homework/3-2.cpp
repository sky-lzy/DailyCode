#include <iostream>
#include <iomanip>
using namespace std;

class Product
{
private:
    double price;
    double discount;
    static double sum;
    static int number;

public:
    Product(double p, double d);
    void account(int n);
    static void print();
};

double Product::sum = 0;
int Product::number = 0;

Product::Product(double p, double d) : price(p), discount(d) {}

void Product::account(int n)
{
    double s = price * discount * n;
    if (n >= 10)
        s *= 0.98;
    sum += s;
    number += n;
}

void Product::print()
{
    cout << "次日总销售款：" << fixed << setprecision(2) << sum << endl
         << "平均销售单价：" << fixed << setprecision(2) << sum / number << endl;
}

int main()
{
    Product p1(23.5, 0.9);
    Product p2(24.5, 0.85);
    Product p3(21.5, 0.95);
    p1.account(5);
    p2.account(12);
    p3.account(100);
    Product::print();
    return 0;
}