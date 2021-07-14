#include <iostream>
#include <string>
#include "employee.h"

int employee::currentEmpNo = 2014001;

void employee::printInfo() const
{
    std::cout << "编号\t姓名\t等级\t月薪" << std::endl;
    std::cout << individualEmpNo << '\t' << name << 't' << grade << 't' << accumpay << std::endl;
}

bool employee::promote(const int gradeUp)
{
    if (grade + gradeUp > 0)
    {
        grade += gradeUp;
        return true;
    }
    else
        return false;
}

employee::employee() : grade(1), accumpay(3000)
{
    individualEmpNo = currentEmpNo++;
    name.clear();
}

employee::employee(const int inputEmpNo, const int inputGrade, const int inputPay, const string inputName)
    : individualEmpNo(inputEmpNo), grade(inputGrade), accumpay(inputPay), name(inputName) {}

employee::~employee()
{
    std::cout << "欢迎使用，再见！" << std::endl;
}

void employee::updateInfo()
{
    std::cout << "请输入编号为" << individualEmpNo << "的雇员的姓名、等级、月薪" << std::endl;
    std::cin >> name >> grade >> accumpay;
}

std::istream &operator>>(std::istream &input, employee &e)
{
    input >> e.individualEmpNo >> e.name >> e.grade >> e.accumpay;
    return input;
}

std::ostream &operator<<(std::ostream &output, const employee &e)
{
    std::cout << e.individualEmpNo << '\t' << e.name << '\t' << e.grade << '\t' << e.accumpay << std::endl;
    return output;
}