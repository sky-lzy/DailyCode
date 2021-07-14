#include <iostream>
using namespace std;

class Date
{
private:
    int d;
    int m;
    int y;

public:
    Date(int dd, int mm, int yy);
    void addDay();
    friend Date operator++(Date &D);      //前置++
    friend Date operator++(Date &D, int); //后置++
    void print();
};

Date::Date(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

Date operator++(Date &D)
{
    D.addDay();
    return D;
}

Date operator++(Date &D,int)
{
    Date temp(D);
    D.addDay();
    return temp;
}