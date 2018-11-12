#include<stdio.h>
#include<conio.h>
void main()
{
	int sum = 0;
	int sum1 = 0;

	for (int i = 0; i <= 100; i++)
	{
		if (i % 2 == 0)
		{
			sum = sum + i;
		}
		else
		{
			sum1 = sum1 + i;
		}
	}
	printf("1~100까지의 짝수의 합:%d\n", sum);
	printf("1~100까지의 홀수의 합:%d\n", sum1);
	printf("1~100까지의 짝수와 홀수의 합:%d\n", sum + sum1);
	_getch();
}