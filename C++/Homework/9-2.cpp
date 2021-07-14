#include <iostream>
using namespace std;

int main()
{
    double x = 123.456;
    cout.width(10);
    cout.setf(ios::dec, ios::basefield);
    cout << x << endl;
    cout.setf(ios::left);
    cout << x << endl;
    cout.width(15);
    cout.setf(ios::right, ios::left);
    cout << x << endl;
    cout.setf(ios::showpos);
    cout << x << endl;
    cout << -x << endl;
    cout.setf(ios::scientific);
    cout << x << endl;
    return 0;
}