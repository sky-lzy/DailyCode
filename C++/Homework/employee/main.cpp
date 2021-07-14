#include <iostream>
#include "employee.h"
using namespace std;

int main()
{
    Employee x1(3, 15000), x2(4,30000), x3(5, 50000), x4(2, 10000); //构建四个员工对象
    Employee x[20];
    x1.getInformation();
    x2.getInformation();
    x3.getInformation();
    x4.getInformation();
    for (int i = 0; i < 20; i++)
    {
        x[i].getInformation();
    }
    
    return 0;
}