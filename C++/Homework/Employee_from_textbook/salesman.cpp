#include <iostream>
#include "salesman.h"
#include "salemanager.h"

void salesman::printInfo() const
{
    std::cout << "岗位\t编号\t姓名\t上司\t等级\t月薪\t销售额\t提成率" << std::endl;
    int bossEmpNo;
    if (getBoss() == NULL)
        bossEmpNo = -1;
    else bossEmpNo = getBoss()->getEmpNo();
}