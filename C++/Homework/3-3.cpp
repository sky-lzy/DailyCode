#include <iostream>
#include <iomanip>
using namespace std;

class Date
{
private:
    int d;
    int m;
    int y;

public:
    Date(int dd = 0, int mm = 0, int yy = 0);
    Date(const Date &D);
    ~Date();
};

Date::Date(int dd, int mm, int yy) : d(dd), m(mm), y(yy)
{
    cout << "Constructor called! Address = 0x"
         << hex << setw(8) << setfill('0') << this << endl;
}

Date::Date(const Date &D)
{
    d = D.d;
    m = D.m;
    y = D.y;
    cout << "Copy constructor called! Address = 0x"
         << hex << setw(8) << setfill('0') << this << endl;
}

Date::~Date()
{
    cout << "Destructor called! Address = 0x"
         << hex << setw(8) << setfill('0') << this << endl;
}

/* 
Date func(Date A)
{
    return Date(A);
}

int main()
{
    Date today;
    today = func(today);
    return 0;
} 
*/

/* 
Date func(Date A)
{
    Date B(A);
    return B;
}

int main()
{
    Date today;
    today = func(today);
    return 0;
}
*/

/* 
Date & func(Date A)
{
    Date B(A);
    return B;
}

int main()
{
    Date today;
    today = func(today);
    return 0;
} 
*/

Date func(Date A)
{
    return A;
}

int main()
{
    Date today;
    today = func(today);
    return 0;
}