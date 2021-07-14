#ifndef SALESMAN_H
#define SALESMAN_H

#define RATE_SALESMAN 0.05
#define PROMOTE_RATE_SALESMAN 0.01

#include "employee.h"

class salemanager;

class salesman : virtual public employee
{
private:
    int sales;
    double commissionRate;
    salemanager *boss;

public:
    salesman();
    salesman(const int inputEmpNo, const int inputGrade, const std::string inputName,
             const int inputSales, const salemanager *inputBoss);
    virtual ~salesman();

    void setCommissionRate(const double inputRate)
    {
        commissionRate = inputRate;
        setAccumPay((int)(sales * commissionRate));
    }
    void setSales(const int inputSales);
    void setBoss(const salemanager *inputBoss);
    double getCommissionRate() const { return commissionRate; }
    int getSales() const { return sales; }
    salemanager *getBoss() const { return boss; }

    virtual void printInfo() const;
    virtual void updateInfo();
    virtual int PAY();
    virtual bool promote(int gradeUp);

    friend std::istream &operator>>(std::istream &, salesman &);
    friend std::ostream &operator<<(std::ostream &, const salesman &);
};

#endif