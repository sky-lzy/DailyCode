#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee //定义Employee类
{
protected:
    int individualEmpNo; //员工编号
    int grade;           //员工等级
    int accumPay;        //员工工资
    static int num;      //默认编号
public:
    Employee();             //默认构造函数
    Employee(int g, int a); //构造员工
    ~Employee();            //析构函数
    void setEmpNo(int i);   //设定编号
    void setGrade(int g);   //设定等级
    void setPay(int a);     //设定工资
    void getInformation();  //获取信息
};

#endif