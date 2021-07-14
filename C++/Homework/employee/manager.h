#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"
class Manager : public Employee
{
public:
    Manager();
    Manager(int g);
};

Manager::Manager() {}

Manager::Manager(int g) : Employee(g,12000) {}

#endif