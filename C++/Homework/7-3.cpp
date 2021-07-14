#include <iostream>
using namespace std;

class TT
{
private:
    int N;
    int D;

public:
    TT(int n = 0, int d = 0);
    void print();
    friend TT Div(TT &r1, TT &r2);
};

TT::TT(int n, int d)
{
    N = n;
    D = d;
}

TT Div(TT &r1, TT &r2)
{
    return TT(r1.N / r2.D + r1.D / r2.N, r1.D / r2.D);
}

void TT::print()
{
    cout << "N = " << N << " D = " << D << endl;
}

int main()
{
    TT a(1,2),b(3,4),c;
    c = Div(a,b);
    c.print();
    return 0;
}