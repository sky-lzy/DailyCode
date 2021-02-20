#include <stdio.h>
#include <math.h>
void trans(int n, char one, char two, char three);
void move(char x, char y);
int main()
{
	int m = 0;
	printf("请输入需要移动的数量n:");
	scanf("%d", &m);
	if (m <= 15 && m > 0)
	{
		printf("共需移动%d次完成\n", (int)(pow(2, m) - 1));
		printf("按以下步骤移动:\n");
		trans(m, 'A', 'B', 'C');
	}
	else if (m > 0 && m <= 31)
		printf("共需%d次完成  （由于次数过多不列出）\n", (unsigned long long int)(pow(2, m) - 1));
	else
		printf("请输入小于32的整数\n");
	printf("\n");
	return 0;
}

void trans(int n, char one, char two, char three)
{
	if (n == 1)
		move(one, three);
	else
	{
		trans(n - 1, one, three, two);
		move(one, three);
		trans(n - 1, two, one, three);
	}
}

void move(char x, char y)
{
	printf("%c-->%c  ", x, y);
}
