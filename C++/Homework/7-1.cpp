#include <iostream>
using namespace std;

class B1
{
public:
    B1(int i)
    {
        cout << "Constructing B1 " << i << endl;
    }
    ~B1()
    {
        cout << "Destructing B1" << endl;
    }
};

class B2
{
public:
    B2()
    {
        cout << "Constructing B3 * " << endl;
    }
    ~B2()
    {
        cout << "Destructing B3" << endl;
    }
};

class C : public B2, virtual public B1
{
private:
    int j;
    B1 memberB1;
    B2 memberB2;

public:
    C(int a, int b, int c) : B1(a), memberB1(b), j(c) {}
};

int main()
{
    C obj(1, 2, 3);
    return 0;
}