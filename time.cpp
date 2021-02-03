#include <iostream>
#include <iomanip>
#include "time.h"
using namespace std;

time::time() : hour(0), min(0), sec(0) {}

time::time(int h, int m, int s) : hour(h), min(m), sec(s) {}

time::~time() {}

void time::ShowTime()
{
    cout << "Time is " << hour << ":" << min << ":" << sec << endl;
}

time time::operator++()
{
    ++sec;
    if (sec >= 60)
    {
        sec -= 60;
        ++min;
    }
    if (min >= 60)
    {
        min -= 60;
        ++hour;
    }
    return *this;
}