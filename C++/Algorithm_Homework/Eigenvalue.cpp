#include <iostream>
#include <iomanip>

double Matrix[1010][1010] = {};
double Vec[1010] = {};
int P[1010] = {};

void MaxEigenvalue(double exact, int N)
{
    double now_exact = 1, last_m = 0;
    Vec[0] = 1;
    while (now_exact > exact)
    {
        //计算 A*x
        double tempVec[1010] = {};
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                tempVec[i] += Matrix[i][j] * Vec[j];

        //归一化
        double max = 0;
        for (int i = 0; i < N; i++)
            if (tempVec[i] > max)
                max = tempVec[i];
        for (int i = 0; i < N; i++)
            Vec[i] = tempVec[i] / max;

        //计算偏差
        now_exact = (max > last_m ? max - last_m : last_m - max) / max;
        last_m = max;
    }
    std::cout << std::setprecision(4) << last_m << " ";
}

void PLU(int N)
{
    //初始化P矩阵
    for (int i = 0; i < N; i++)
        P[i] = i;

    //PLU分解
    for (int i = 0; i < N; i++)
    {
        //选出最大值
        double temp_max = 0;
        int temp_max_row = 0;
        for (int j = i; j < N; j++)
            // if (Matrix[j][i] > temp_max)
            if ((Matrix[j][i] > 0 ? Matrix[j][i] : -Matrix[j][i]) > temp_max)
            {
                // temp_max = Matrix[j][i];
                temp_max = Matrix[j][i] > 0 ? Matrix[j][i] : -Matrix[j][i];
                temp_max_row = j;
            }

        //交换
        std::swap(P[i], P[temp_max_row]);
        for (int j = 0; j < N; j++)
            std::swap(Matrix[i][j], Matrix[temp_max_row][j]);

        //计算LU分解
        for (int j = i + 1; j < N; j++)
        {
            Matrix[j][i] /= Matrix[i][i];
            for (int k = i + 1; k < N; k++)
                Matrix[j][k] -= Matrix[j][i] * Matrix[i][k];
        }
    }
}

void MinEigenvalue(double exact, int N)
{
    //初始化
    double now_exact = 1, last_m = 0;
    Vec[0] = 1;
    for (int i = 1; i < N; i++)
        Vec[i] = 0;

    while (now_exact > exact)
    {
        double tempVec[1010] = {};

        //计算 P * v
        for (int i = 0; i < N; i++)
            tempVec[i] = Vec[P[i]];

        //计算 L^-1 * v
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                tempVec[j] += -Matrix[j][i] * tempVec[i];

        //计算 U^-1 * v
        for (int i = N - 1; i >= 0; i--)
        {
            tempVec[i] /= Matrix[i][i];
            for (int j = i - 1; j >= 0; j--)
                tempVec[j] += -Matrix[j][i] * tempVec[i];
        }

        //归一化
        double max = 0;
        for (int i = 0; i < N; i++)
            if (tempVec[i] > max)
                max = tempVec[i];
        for (int i = 0; i < N; i++)
            Vec[i] = tempVec[i] / max;

        //计算偏差
        now_exact = (max > last_m ? max - last_m : last_m - max) / max;
        last_m = max;
    }
    std::cout << std::setprecision(4) << 1 / last_m << " ";
}

int main()
{
    //读取数据
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%lf", &Matrix[i][j]);

    //幂法求解最大特征值
    MaxEigenvalue(1e-10, N);

    //求PLU分解
    PLU(N);

    //反幂法求最小特征值
    MinEigenvalue(1e-10, N);
    std::cout << std::endl;

    return 0;
}