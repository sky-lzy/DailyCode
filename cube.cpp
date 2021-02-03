#include <iostream>
using namespace std;

class Cube
{
private:
    int height;
    int width;
    int length;

public:
    Cube(int = 10, int = 10, int = 10);
    Cube(const Cube &x);
    ~Cube();
    int volume();
};

Cube::Cube(int h, int w, int len) : height(h), width(w), length(len)
{
    cout << "调用普通构造函数" << endl;
}

Cube::~Cube()
{
    cout << "调用析构函数" << endl;
}

Cube::Cube(const Cube &x)
{
    height = x.height;
    width = x.width;
    length = x.length;
    cout << "调用复制构造函数" << endl;
}

int Cube::volume()
{
    return (height * width * length);
}

int main()
{
    Cube cube1(10, 25, 30), cube2;
    cout << "The volume of cube1 is " << cube1.volume() << endl;
    cube2 = cube1;
    Cube cube3(cube2);
    Cube *p = new Cube(cube3);
    delete p;
    cout << "The volume of cube2 is " << cube2.volume() << endl;
    cout << "The volume of cube3 is " << cube3.volume() << endl;
    return 0;
}