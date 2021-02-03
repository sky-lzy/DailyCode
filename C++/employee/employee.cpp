#include <iostream>
#include "employee.h"
using namespace std;

int employee::currentEmpNo = 2020001;

void employee::printInfo()
{
    cout << "输出个人信息：" << endl;
    cout << "编号：" << individualEmpNo << endl;
    cout << "等级：" << grade << endl;
    cout << "月薪：" << accumPay << endl
         << endl;
}

employee::employee()
{
    individualEmpNo = currentEmpNo;
    currentEmpNo++;
    grade = 1;
    accumPay = 3000;
}

employee::employee(int inputGrade, int inputPay)
{
    individualEmpNo = currentEmpNo;
    currentEmpNo++;
    grade = inputGrade;
    accumPay = inputPay;
}

employee::~employee()
{
    cout << "欢迎使用，再见！" << endl;
}

void employee::setGrade(int inputGrade)
{
    grade = inputGrade;
}

void employee::setAccumPay(int inputPay)
{
    accumPay = inputPay;
}

int employee::getEmpNo()
{
    return individualEmpNo;
}

int employee::getGrade()
{
    return grade;
}

int employee::getAccumPay()
{
    return accumPay;
}