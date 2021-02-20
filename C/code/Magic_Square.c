#include <stdio.h>
#include <stdlib.h>

void order_a(int x1, int x2, int y1, int y2, int z1, int z2); //奇数幻方填写
void order_b(int m);										  //按顺序初始化数组
void printfx(int m);										  //输出幻方
void swap(int x1, int x2, int y1, int y2);					  //元素交换

int a[50][50] = {0}; //幻方数组

int main()
{
	int n = 0;
	printf("请输入你想得到的n阶幻方(3~32):");
	scanf("%d", &n);
	if (n > 2 && n <= 32)
	{
		if (n % 2 == 1) //奇数阶幻方
		{
			order_a(0, n - 1, 0, n - 1, 1, n * n);
		}
		else if (n % 4 == 0) //双偶数阶幻方
		{
			order_b(n); //顺序排列幻方
			int s = n * n + 1;
			int i = 0, j = 0;
			for (i = 0; i < n; i++) //对角线元素取补
			{
				for (j = 0; j < n; j++)
				{
					if (i % 4 == 0 || i % 4 == 3)
					{
						if (j % 4 == 0 || j % 4 == 3)
							a[i][j] = s - a[i][j];
					}
					else if (j % 4 == 1 || j % 4 == 2)
						a[i][j] = s - a[i][j];
				}
			}
		}
		else if (n % 4 == 2) //单偶数阶幻方
		{
			order_a(0, n / 2 - 1, 0, n / 2 - 1, 1, n * n / 4); //分成四个模块，分别按奇数阶幻方填写
			order_a(n / 2, n - 1, n / 2, n - 1, n * n / 4 + 1, n * n / 2);
			order_a(0, n / 2 - 1, n / 2, n - 1, n * n / 2 + 1, n * n * 3 / 4);
			order_a(n / 2, n - 1, 0, n / 2 - 1, n * n * 3 / 4 + 1, n * n);
			int k = (n - 2) / 4;
			if (k > 0)
			{
				int i = 0, j = 0;
				for (j = 0; j < k; j++) //从第二象限中心开始k格与第三象限交换
				{
					swap(k, k + j, n / 2 + k, k + j);
				}
				for (i = 0; i < k; i++) //第二象限开始k阶与第三象限交换
				{
					for (j = 0; j < k; j++)
					{
						swap(i, j, i + n / 2, j);
					}
				}
				for (i = k + 1; i < n / 2; i++) //第二象限下面k阶与第三象限交换
				{
					for (j = 0; j < k; j++)
					{
						swap(i, j, i + n / 2, j);
					}
				}
			}
			if (k > 1)
			{
				int i = 0, j = 0;
				for (i = 0; i < n / 2; i++) //第一象限第二列开始k列于第四象限交换
				{
					for (j = n / 2 + 2; j <= n / 2 + k; j++)
					{
						swap(i, j, i + n / 2, j);
					}
				}
			}
		}
		printfx(n); //输出幻方
	}
	else
		printf("请输入3~32范围内的整数\n");
	return 0;
}

void order_a(int x1, int x2, int y1, int y2, int z1, int z2) //奇数幻方填写
{
	int t1 = x1, t2 = (y1 + y2) / 2;
	int z = z1;
	for (z = z1; z <= z2; z++)
	{
		a[t1][t2] = z;
		t1 -= 1;
		t2 += 1;
		if (t1 == x1 - 1 && t2 <= y2)
			t1 = x2;
		if (t2 == y2 + 1 && t1 >= x1)
			t2 = y1;
		if (t1 == x1 - 1 && t2 == y2 + 1)
		{
			t1 = x1 + 1;
			t2 = y2;
		}
		if (a[t1][t2] != 0)
		{
			t1 += 2;
			t2 -= 1;
		}
	}
}

void order_b(int m) //按顺序初始化数组
{
	int i = 0, j = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			a[i][j] = m * i + j + 1;
		}
	}
}

void printfx(int m) //输出幻方
{
	int i = 0, j = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (a[i][j] < 10)
				printf("   ");
			else if (a[i][j] < 100)
				printf("  ");
			else if (a[i][j] < 1000)
				printf(" ");
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

void swap(int x1, int x2, int y1, int y2) //元素交换
{
	int t = a[x1][x2];
	a[x1][x2] = a[y1][y2];
	a[y1][y2] = t;
}
