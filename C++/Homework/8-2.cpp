#include <iostream>
using namespace std;

class Mammal
{
public:
    virtual void speak();
};

void Mammal::speak()
{
    cout << "我是一只哺乳动物！" << endl;
}

class Dog : public Mammal
{
public:
    virtual void speak();
};

void Dog::speak()
{
    cout << "我是一只狗，汪汪！" << endl;
}

int main()
{
    Dog d;
    d.speak();
    Mammal *p = &d;
    p->speak();
    return 0;
}