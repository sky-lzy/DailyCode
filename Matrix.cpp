#include <iostream>
#include <assert.h>
#include <iomanip>
using namespace std;

class Matrix
{
private:
    double *data;
    int row;
    int col;

public:
    Matrix();
    Matrix(double *, int, int);
    ~Matrix();
    double &operator()(int, int);
};

Matrix::Matrix() : data(NULL), row(0), col(0) {}

Matrix::Matrix(double *pData, int r, int c) : data(pData), row(r), col(c) {}

Matrix::~Matrix()
{
    delete[] data;
}

double &Matrix::operator()(int r, int c)
{
    assert(r >= 0 && r < row && c >= 0 && c < col);
    return data[col * r + c];
}

int main()
{
    double *pData = new double[100];
    int row = 10;
    int col = 10;
    Matrix m(pData, row, col);

    int cnt = 1;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m(i, j) = cnt++;
            cout << setw(2) << m(i, j) << ' ';
        }
        cout << endl;
    }
    return 0;
}