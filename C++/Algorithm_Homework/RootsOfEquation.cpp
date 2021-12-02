#include <iostream>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <vector>
#include <cmath>

#define MIN_DIS 5e-2
#define OUTPUT_NUM 10
#define FIRST_EXACT 5e-3
#define MIN_EXACT 1e-11

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
    std::complex<double> Fun(const std::complex<double> &input) const;                     //计算函数值
    std::complex<double> DFun(const std::complex<double> &input, int weight) const;        //N阶导数函数值
    void Aberth();                                                                         //求Aberth初始值
    bool Iter();                                                                           //方程迭代
    void SortRoots();                                                                      //排序
    void Newton();                                                                         //牛顿法迭代
    std::complex<double> NewtonSolve(const std::complex<double> &input, int weight) const; //牛顿法求重根
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

std::complex<double> Equation::Fun(const std::complex<double> &input) const
{
    std::complex<double> output = 0;
    for (int i = 0; i <= N; i++)
        output += pow(input, i) * Coe[i];
    return output;
}

std::complex<double> Equation::DFun(const std::complex<double> &input, int weight) const
{
    std::complex<double> tempComplex(0, 0);
    for (int i = weight; i <= N; i++)
    {
        int tempcoe = 1;
        for (int j = 0; j < weight; j++)
            tempcoe *= (i - j);
        tempComplex += Coe[i] * tempcoe * pow(input, i - weight);
    }
    return tempComplex;
}

void Equation::Aberth()
{
    double r = 150;
    double Zc = -1 / N * Coe[N - 1] / Coe[N];
    for (int i = 0; i < N; i++)
    {
        double angle = 2 * 3.1415926536 / N * i + 3.1415926536 / 2 / N;
        Sol[i] = std::complex<double>(Zc, 0) + r * std::complex<double>(cos(angle), sin(angle));
    }
}

void Equation::print()
{

    std::cout << std::setprecision(OUTPUT_NUM);
    for (auto i : Sol)
    {
        if (i.real() < MIN_DIS && i.real() > -MIN_DIS)
            i = i - i.real();
        if (i.imag() > MIN_DIS)
            std::cout << i.real() << " " << i.imag() << "\n"
                      << i.real() << " " << -i.imag() << "\n";
        // else if (i.imag() > -MIN_DIS)
        else
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
        tempS = std::max(tempS, abs(e));
    }
    Sol.swap(temp);
    return tempS < FIRST_EXACT;
}

void Equation::Solve()
{
    Aberth();
    while (!Iter())
        ;
    SortRoots();
    Newton();
}

void Equation::SortRoots()
{
    std::sort(Sol.begin(), Sol.end(), [](const std::complex<double> &com1, const std::complex<double> &com2) -> bool
              {
                  if (com1.real() - com2.real() < MIN_DIS && com1.real() - com2.real() > -MIN_DIS)
                      return com1.imag() > com2.imag();
                  else
                      return com1.real() > com2.real();
              });
}

void Equation::Newton()
{
    std::vector<std::complex<double>> tempSolve;
    for (int i = 0; i < N; i++)
    {
        double tempReal = Sol[i].real();
        // bool kind = fabs(Sol[i].imag()) < MIN_DIS ? true : false; //是否实根 true实根，false虚根
        int weight = 1; //根的重数
        while (i < N - 1 && fabs(Sol[i + 1].real() - tempReal) < MIN_DIS)
        {
            i++;
            if (Sol[i].imag() > -MIN_DIS)
                weight++;
        }
        std::complex<double> tempComplex = NewtonSolve(Sol[i], weight);
        for (int j = 0; j < weight; j++)
            tempSolve.emplace_back(tempComplex);
    }
    Sol.swap(tempSolve);
}

std::complex<double> Equation::NewtonSolve(const std::complex<double> &input, int weight) const
{
    std::complex<double> tempComplex(input);
    double tempS = 999;
    while (tempS > MIN_EXACT)
    {
        std::complex<double> Complex_1 = tempComplex - DFun(tempComplex, weight - 1) / DFun(tempComplex, weight);
        // tempS = std::max(fabs(tempComplex.real() - Complex_1.real()), fabs(tempComplex.imag() - Complex_1.imag()));
        tempS = abs(tempComplex - Complex_1);
        tempComplex = Complex_1;
    }
    return std::complex<double>(tempComplex.real(), fabs(tempComplex.imag()));
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