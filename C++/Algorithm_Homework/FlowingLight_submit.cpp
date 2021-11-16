#include <iostream>
#include <vector>
#include <stack>

bool b[1001];        //操作B
bool t[1001];        //目标T
bool dec[1001];      //T在基底上的分解
bool Ab[1001][1001]; //线性空间V基底
class Light
{
    //内置数据
private:
    int n; //维度

    //外部接口
public:
    Light(int inputN);
    bool Decompose();
    inline void print() const;

    //内部实现方法
private:
    void ReadB();
    void ReadT();
    void CalculateAb();
    void Row_xor(int r1, int r2, int begin = 0);
    void Row_exchange(int r1, int r2, int begin = 0);
};

Light::Light(int inputN) : n(inputN)
{
    ReadB();
    ReadT();
    CalculateAb();
}

void Light::ReadB()
{
    char temp = getchar();
    while (temp != '0' && temp != '1')
        temp = getchar();
    for (int i = 0; i < n; i++)
    {
        b[i] = temp - '0';
        temp = getchar();
    }
}

void Light::ReadT()
{
    char temp = getchar();
    while (temp != '0' && temp != '1')
        temp = getchar();
    for (int i = 0; i < n; i++)
    {
        t[i] = temp - '0';
        temp = getchar();
    }
}

void Light::CalculateAb()
{
    std::vector<int> temp(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            Ab[i][(j + i) % n] = b[j];
    }
}

bool Light::Decompose()
{
    std::vector<int> MainList(n); //主元列表

    //化成上三角阵
    int row = 0, column = 0;
    for (; column < n; column++)
    {
        //找到column的主元，与当前行交换，不存在跳过此列
        int temp_row = row;
        for (; temp_row < n && !Ab[column][temp_row]; temp_row++)
            ;
        if (temp_row == n)
            continue;
        MainList[row] = column;
        Row_exchange(row, temp_row, column);

        //Gauss消去后面所有此元
        for (temp_row = row + 1; temp_row < n; temp_row++)
            if (Ab[column][temp_row])
                Row_xor(temp_row, row, column);

        //下一行
        row++;
    }

    //判定解是否存在
    for (int temp_row = row; temp_row < n; temp_row++)
        if (t[temp_row])
            return false;

    //向上消至行最简阵
    for (int temp_row = row - 1; temp_row >= 0; temp_row--)
    {
        //找到主元
        int main = MainList[temp_row]; //主元
        dec[temp_row] = t[temp_row];

        //向上消去
        for (int i = temp_row - 1; i >= 0; i--)
            if (Ab[main][i])
                // Row_xor(i, temp_row);
                t[i] = t[i] ^ t[temp_row];
    }
    return true;
}

void Light::print() const
{
    std::stack<bool> oper; //操作型：0为A，1为B
    int temp_i = 0;
    for (int i = 0; i < n; i++)
    {
        if (dec[i])
        {
            for (int j = 0; j < i - temp_i; j++)
                oper.emplace(false);
            oper.emplace(true);
            temp_i = i;
        }
    }

    if (oper.empty())
    {
        printf("A\n");
        return;
    }

    while (!oper.empty())
    {
        if (oper.top())
            printf("B");
        else
            printf("A");
        oper.pop();
    }
    printf("\n");
}

void Light::Row_xor(int r1, int r2, int begin)
{
    for (int i = begin; i < n; i++)
        Ab[i][r1] = Ab[i][r1] ^ Ab[i][r2];
    t[r1] = t[r1] ^ t[r2];
}

void Light::Row_exchange(int r1, int r2, int begin)
{
    if (r1 == r2)
        return;

    for (int i = begin; i < n; i++)
        std::swap(Ab[i][r1], Ab[i][r2]);
    std::swap(t[r1], t[r2]);
}

class Light2
{
    //内置数据
private:
    int n;                              //维度
    std::vector<bool> b2;               //操作B
    std::vector<bool> t2;               //目标T
    std::vector<bool> dec2;             //T在基底上的分解
    std::vector<std::vector<bool>> Ab2; //线性空间V基底

    //外部接口
public:
    Light2(int inputN);
    bool Decompose();
    inline void print() const;

    //内部实现方法
private:
    void ReadB();
    void ReadT();
    void CalculateAb();
    void Row_xor(int r1, int r2, int begin = 0);
    void Row_exchange(int r1, int r2, int begin = 0);
};

Light2::Light2(int inputN) : n(inputN), b2(inputN), t2(inputN), dec2(inputN, 0), Ab2(inputN, std::vector<bool>(n))
{
    ReadB();
    ReadT();
    CalculateAb();
}

void Light2::ReadB()
{
    char temp = getchar();
    while (temp != '0' && temp != '1')
        temp = getchar();
    for (int i = 0; i < n; i++)
    {
        b2[i] = temp - '0';
        temp = getchar();
    }
}

void Light2::ReadT()
{
    char temp = getchar();
    while (temp != '0' && temp != '1')
        temp = getchar();
    for (int i = 0; i < n; i++)
    {
        t2[i] = temp - '0';
        temp = getchar();
    }
}

void Light2::CalculateAb()
{
    std::vector<int> temp(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            Ab2[i][(j + i) % n] = b2[j];
    }
}

bool Light2::Decompose()
{
    std::vector<int> MainList(n); //主元列表

    //化成上三角阵
    int row = 0, column = 0;
    for (; column < n; column++)
    {
        //找到column的主元，与当前行交换，不存在跳过此列
        int temp_row = row;
        for (; temp_row < n && !Ab2[column][temp_row]; temp_row++)
            ;
        if (temp_row == n)
            continue;
        MainList[row] = column;
        Row_exchange(row, temp_row, column);

        //Gauss消去后面所有此元
        for (temp_row = row + 1; temp_row < n; temp_row++)
            if (Ab2[column][temp_row])
                Row_xor(temp_row, row, column);

        //下一行
        row++;
    }

    //判定解是否存在
    for (int temp_row = row; temp_row < n; temp_row++)
        if (t2[temp_row])
            return false;

    //向上消至行最简阵
    for (int temp_row = row - 1; temp_row >= 0; temp_row--)
    {
        //找到主元
        int main = MainList[temp_row]; //主元
        dec2[temp_row] = t2[temp_row];

        //向上消去
        for (int i = temp_row - 1; i >= 0; i--)
            if (Ab2[main][i])
                // Row_xor(i, temp_row);
                t2[i] = t2[i] ^ t2[temp_row];
    }
    return true;
}

void Light2::print() const
{
    std::stack<bool> oper; //操作型：0为A，1为B
    int temp_i = 0;
    for (int i = 0; i < n; i++)
    {
        if (dec2[i])
        {
            for (int j = 0; j < i - temp_i; j++)
                oper.emplace(false);
            oper.emplace(true);
            temp_i = i;
        }
    }

    if (oper.empty())
    {
        printf("A\n");
        return;
    }

    while (!oper.empty())
    {
        if (oper.top())
            printf("B");
        else
            printf("A");
        oper.pop();
    }
    printf("\n");
}

void Light2::Row_xor(int r1, int r2, int begin)
{
    for (int i = begin; i < n; i++)
        Ab2[i][r1] = Ab2[i][r1] ^ Ab2[i][r2];
    t2[r1] = t2[r1] ^ t2[r2];
}

void Light2::Row_exchange(int r1, int r2, int begin)
{
    if (r1 == r2)
        return;

    for (int i = begin; i < n; i++)
        std::swap(Ab2[i][r1], Ab2[i][r2]);
    std::swap(t2[r1], t2[r2]);
}

int main()
{
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int n;
        scanf("%d", &n);
        if (n < 500)
        {
            Light2 light2(n);
            if (light2.Decompose())
                light2.print();
            else
                printf("N\n");
        }
        else
        {
            Light light(n);
            if (light.Decompose())
                light.print();
            else
                printf("N\n");
        }
    }

    return 0;
}