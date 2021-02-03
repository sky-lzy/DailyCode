#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class employee
{
private:
    int individualEmpNo;
    int grade;
    int accumPay;
    static int currentEmpNo;
public:
    employee();
    employee(int inputGrade, int intputPay);
    ~employee();

    void setGrade(int inputGrade);
    void setAccumPay(int inputPay);
    int getEmpNo();
    int getGrade();
    int getAccumPay();

    void printInfo();
};

#endif