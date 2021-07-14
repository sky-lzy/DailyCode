#ifndef MANAGER_H
#define MANAGER_H

#define FIXED_PAY_MANAGER 12000
#define PROMOTE_PAY_MANAGER 4000

#include "employee.h"

class manager : virtual public employee
{
private:
    int fixed_pay;

public:
    manager();
    manager(const int inputEmpNo, const int inputGrade, const string inputName);

    virtual ~manager();

    void setFixedPay(const int inputPay) { fixed_pay = inputPay; };
    int getFixedPay() const { return fixed_pay; };

    virtual void printInfo() const;
    virtual void updateInfo();
    virtual int PAY();
    virtual bool promote(const int gradeUp);

    friend std::istream &operator>>(std::istream &, manager &);
    friend std::ostream &operator<<(std::ostream &, const manager &);
};

#endif