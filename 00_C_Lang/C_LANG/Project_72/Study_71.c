#include<stdio.h>
#include<conio.h>

void HanioTab(int n, char from, char temp, char to)
{
	if (n > 0)
	{
		HanioTab(n - 1, from, to, temp);
		printf("[%d] %c-->%c\n", n, from, to);
		HanioTab(n - 1, temp, from, to);
	}
}
void HanioTower(int n, char from, char temp, char to)
{
	if (n == 1)
	{
		printf("[%d] %c-->%c\n", n, from, to);
	}
	else
	{
		HanioTower(n - 1, from, to, temp);
		printf("[%d]%c-->%c\n", n, from, to);
		HanioTower(n - 1, temp, from, to);
	}
}

int factorial(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else
	{
		int iRet = factorial(n - 1);
		return n * iRet;
	}
}

void main()
{
	int sum = 1;

	for (int i = 1; i <= 3; i++)
	{
		sum = sum * i;
	}
	printf("\n%d", sum);
	printf("\n%d", factorial(5));

	int n;
	printf("¿ø¹Ý °¹¼ö...?");
	scanf_s("%d", &n);

	HanioTower(n, 'a', 'b', 'c');
	_getch();
}