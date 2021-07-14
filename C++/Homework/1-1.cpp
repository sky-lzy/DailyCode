#include <iostream>
using namespace std;

enum CPURank {P1 = 1, P2, P3, P4, P5, P6, P7};

class CPU
{
private:
    enum CPURank rank;
    int frequency;
    double voltage;
public:
    void enter(int r, int f, double v);
    void display();
};

void CPU::enter(int r, int f, double v)
{
    rank = (CPURank) r;
    frequency = f;
    voltage = v;
}

void CPU::display()
{
    cout << "该CPU的等级为" << rank << endl
         << "频率为" << frequency << "MHz" <<endl
         << "电压为" << voltage << "V" << endl;
}

int main()
{
    CPU CPU_1, CPU_2;
    CPU_1.enter(3, 923, 0.45);
    CPU_2.enter(6, 580, 0.90);
    CPU_1.display();
    CPU_2.display();
    return 0;
}