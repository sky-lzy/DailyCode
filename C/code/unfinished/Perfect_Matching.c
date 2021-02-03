#include <stdio.h> //程序未完成，不能编译！

int arrive(int x, int **matrix, int **out); //判断A中各点是否可达

int connect(int y, int **matrix, int **out); //判断B中非T的点是否与S相连

int match(int **matrix, int **out, int n) //进行匈牙利算法步骤
{
    int S[11] = {0}, T[11] = {0};
    int i, j, k, flag;
}

int main(int argc, int *argv[])
{
    int matrix[11][11] = {0}, out[11][11] = {0}; //定义关联矩阵与匹配矩阵
    int n, m, i;
    printf("请输入双方人数 n 与关联关系数量 m ：");
    scanf("%d", &n);
    printf("请输入关联序号：");
    for (i = 0; i < m; i++) //初始化关联矩阵
    {
        int j, k;
        scanf("%d%d", &j, &k);
        matrix[j][k] = 1;
        matrix[k][j] = 1;
    }
    if (match(matrix, out, n)) //判断是否具有完美匹配
    {
        int j, k;
        printf("此图具有完美匹配如下：\n");
        for (j = 1; i < n; j++)
            for (k = j + 1; k <= n; k++)
                if (out[j][k])
                    printf("%d--%d\n", j, k);
    }
    else
        printf("此图不具有完美匹配\n");
    return 0;
}