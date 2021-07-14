#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

class Matrix //矩阵类
{
private:
    int row;      //行数
    int column;   //列数
    double *data; //数据

public:
    Matrix();                              //默认构造函数
    Matrix(int r, int c, const double *d); //含参构造函数
    Matrix(const Matrix &);                //拷贝构造函数
    ~Matrix();                             //析构函数
    double &operator()(int i, int j);      //重载运算符：()
    Matrix operator*(const Matrix &);      //重载运算符：*
    void show();                           //显示矩阵函数
};

Matrix::Matrix()
{
    row = 0;
    column = 0;
    data = NULL;
}

Matrix::Matrix(int r, int c, const double *d) : row(r), column(c)
{
    data = new double[r * c];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            data[i * column + j] = d[i * column + j];
}

Matrix::Matrix(const Matrix &m) : row(m.row), column(m.column)
{
    data = new double[row * column];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            data[i * column + j] = m.data[i * column + j];
}

Matrix::~Matrix()
{
    delete[] data;
}

double &Matrix::operator()(int i, int j)
{
    assert(i >= 0 && i < row && j >= 0 && j < column);
    return data[i * column + j];
}

Matrix Matrix::operator*(const Matrix &m)
{
    assert(column == m.row);
    double *d = new double[row * m.column];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < m.column; j++)
        {
            double t = 0;
            for (int k = 0; k < column; k++)
            {
                t += data[i * column + k] * m.data[k * m.column + j];
            }
            d[i * m.column + j] = t;
        }
    }
    Matrix temp(row, m.column, d);
    return temp;
}

void Matrix::show()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            cout << data[i * column + j] << " ";
        cout << endl;
    }
}

int main()
{
    double x1[6] = {1, 2, 3, 4, 5, 6}, x2[6] = {1, 4, 2, 5, 3, 6};
    Matrix A(2, 3, x1), B(3, 2, x2);
    Matrix C(A * B);
    C.show();
    return 0;
}