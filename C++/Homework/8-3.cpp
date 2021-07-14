#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Shape
{
public:
    Shape() {}
    ~Shape() {}
    virtual double GetArea() = 0;
    virtual double GetPerim() = 0;
};

class Rectangle : public Shape
{
private:
    double a;
    double b;
    double c;

public:
    Rectangle(double aa = 0, double bb = 0, double cc = 0);
    virtual double GetArea();
    virtual double GetPerim();
};

Rectangle::Rectangle(double aa, double bb, double cc) : a(aa), b(bb), c(cc) {}

double Rectangle::GetArea()
{
    double p = (a + b + c) / 2;
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}

double Rectangle::GetPerim()
{
    return a + b + c;
}

class Circle : public Shape
{
private:
    double r;
public:
    Circle(double rr = 0);
    virtual double GetArea();
    virtual double GetPerim();
};

Circle::Circle(double rr) : r(rr) {}

double Circle::GetArea()
{
    return 3.1415926 * r * r;
}

double Circle::GetPerim()
{
    return 3.1415926 * 2 * r;
}

int main()
{
    vector<Shape*> p;
    p.push_back(new(Rectangle)(3,4,5));
    p.push_back(new(Circle)(10));
    cout << "三边长为3，4，5的三角形面积为" << p[0]->GetArea() << endl
    << "周长为" << p[0]->GetPerim() << endl;
    cout << "半径为10的圆的面积为" << p[1]->GetArea() << endl
    << "周长为" << p[1]->GetPerim() << endl;
    delete p[0];
    delete p[1];
    return 0;
}