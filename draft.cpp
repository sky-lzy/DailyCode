#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a = 3141.5926535;
    cout << "a = " << setprecision(10) << a << endl;
    cout << setprecision(4) << "a = " << a << endl;
    cout << fixed << setprecision(4) << "a = " << a << endl;
    return 0;
}