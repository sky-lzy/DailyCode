#include <iostream>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <vector>
#include <cmath>

#define MIN_DIS 5e-4
#define OUTPUT_NUM 8
#define MIN_EXACT 1e-10

class Equation
{
private:
    int N;                                 //方程阶数
    double exact;                          //精度要求
    std::vector<double> Coe;               //系数
    std::vector<std::complex<double>> Sol; //解

public:
    Equation(int inputN, double inputExact);
    // ~Equation();
    void print();
    void Solve();

private:
    std::complex<double> Fun(const std::complex<double> &input); //计算函数值
    void Aberth();                                               //求Aberth初始值
    bool Iter();                                                 //方程迭代
};

Equation::Equation(int inputN, double inputExact) : N(inputN), exact(inputExact), Coe(inputN + 1), Sol(inputN)
{
    double temp = 0;
    for (int i = N; i >= 0; i--)
    {
        scanf("%lf", &temp);
        Coe[i] = temp;
    }
}

std::complex<double> Equation::Fun(const std::complex<double> &input)
{
    std::complex<double> output = 0;
    for (int i = 0; i <= N; i++)
        output += pow(input, i) * Coe[i];
    return output;
}

void Equation::Aberth()
{
    double r = 150;
    double Zc = -1 / N * Coe[N - 1] / Coe[N];
    for (int i = 0; i < N; i++)
    {
        double angle = 2 * 3.1415926536 / N * i + 2 * 3.1415926536 / 2 / N;
        Sol[i] = Zc + r * std::complex<double>(cos(angle), sin(angle));
    }
}

void Equation::print()
{
    std::sort(Sol.begin(), Sol.end(), [](const std::complex<double> &com1, const std::complex<double> &com2) -> bool
              {
                  if (com1.real() - com2.real() < MIN_DIS && com1.real() - com2.real() > -MIN_DIS)
                      return com1.imag() > com2.imag();
                  else
                      return com1.real() > com2.real();
              });

    std::cout << std::setprecision(OUTPUT_NUM);
    for (auto i : Sol)
    {
        if (i.real() < MIN_DIS && i.real() > -MIN_DIS)
            i = i - i.real();
        if (i.imag() > MIN_DIS)
            std::cout << i.real() << " " << i.imag() << "\n"
                      << i.real() << " " << -i.imag() << "\n";
        else if (i.imag() > -MIN_DIS)
            std::cout << i.real() << " " << 0 << "\n";
    }
}

bool Equation::Iter()
{
    std::vector<std::complex<double>> temp(N);
    double tempS = 0;
    for (int i = 0; i < N; i++)
    {
        std::complex<double> tempAll(1, 0);
        for (int j = 0; j < N; j++)
            if (i != j)
                tempAll *= (Sol[i] - Sol[j]);
        temp[i] = Sol[i] - Fun(Sol[i]) / Coe[N] / tempAll;
        auto e = temp[i] - Sol[i];
        if (fabs(e.real()) > tempS)
            tempS = fabs(e.real());
        if (fabs(e.imag()) > tempS)
            tempS = fabs(e.imag());
    }
    Sol.swap(temp);
    return tempS < exact;
}

void Equation::Solve()
{
    Aberth();
    while (!Iter())
        ;
}

int main()
{
    int N;
    scanf("%d", &N);
    Equation equation(N, MIN_EXACT);
    equation.Solve();
    equation.print();
    return 0;
}