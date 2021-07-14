#include <iostream>
#include "manager.h"

void manager::printInfo() const
{
    std::cout << "岗位\t编号\t姓名\t等级\t月薪\t" << std::endl;
    std::cout << "经理\t" << getEmpNo() << '\t' << getName() << '\t' << getGrade << '\t' << getAccumPay << std::endl;
}

int manager::PAY()
{
    setAccumPay(fixed_pay);
    return fixed_pay;
}

bool manager::promote(const int gradeUp)
{
    int grade_temp = getGrade();
    if (grade_temp + gradeUp > 0)
    {
        grade_temp += gradeUp;
        fixed_pay = FIXED_PAY_MANAGER + PROMOTE_PAY_MANAGER * (grade_temp - 1);

        setGrade(grade_temp);
        PAY();
        return true;
    }
    return false;
}

manager::manager() : employee(0, 1, FIXED_PAY_MANAGER, "") {}

manager::manager(const int inputEmpNo, const int inputGrade, const string inputName)
    : employee(inputEmpNo, 1, FIXED_PAY_MANAGER, inputName)
{
    promote(inputGrade - 1);
}

manager::~manager() {}

void manager::updateInfo()
{
    std::cout << "请输入编号为" << getEmpNo() << "的雇员的姓名、等级：" << std::endl;
    int tempGrade;
    std::string tempName;
    std::cin >> tempName >> tempGrade;
    setName(tempName);
    promote(tempGrade - getGrade());
}

std::istream &operator>>(std::istream &input, manager &m)
{
    int tempEmpNo, tempGrade, tempPay;
    std::string tempName;
    input >> tempEmpNo >> tempName >> tempGrade >> tempPay;
    m.setEmpNo(tempEmpNo);
    m.setName(tempName);
    m.promote(tempGrade - m.getGrade());
    return input;
}

std::ostream &operator<<(std::ostream &output, const manager &m)
{
    output << m.getEmpNo() << '\t' << m.getName() << '\t' << m.getGrade() << '\t' << m.getAccumPay() << std::endl;
    return output;
}