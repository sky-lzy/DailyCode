#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
using std::string;

class employee
{
private:
    int individualEmpNo;
    int grade;
    int accumpay;

    string name;

    static int currentEmpNo;

public:
    employee();
    employee(const int inputEmpNo, const int inputGrade, const int inputPay, const string inputName);

    virtual ~employee();

    void setEmpNo(const int inputEmpNo) { individualEmpNo = inputEmpNo; };
    void setGrade(const int inputGrade) { grade = inputGrade; };
    void setAccumPay(const int inputPay) { accumpay = inputPay; };
    int getEmpNo() const { return individualEmpNo; };
    int getGrade() const { return grade; };
    int getAccumPay() const { return accumpay; };

    void setName(const string inputName) { name = inputName; };
    string getName() const { return name; };

    virtual void printInfo() const;
    virtual void updateInfo();
    virtual int PAY() { return accumpay; };
    virtual bool promote(const int gradeUp);

    friend std::istream &operator>>(std::istream &, employee &);
    friend std::ostream &operator<<(std::ostream &, const employee &);
};

#endif