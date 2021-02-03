#include <iostream>
#include "employee.h"
using namespace std;

int main()
{
    employee emp1,emp2;
    employee emp3(2,5000);
    employee emp4(3,7000);
    employee emp5(5,11000);

    int emp1_Grade = 4;
    int emp1_Pay = 9000;

    emp1.setGrade(emp1_Grade);
    emp1.setAccumPay(emp1_Pay);

    emp1.printInfo();
    emp2.printInfo();
    emp3.printInfo();
    emp4.printInfo();
    emp5.printInfo();

    return 0;
}