#include<stdio.h>

void main()
{
	int sum = 0;
	int sum1 = 0;
	int max = 0;
	int iCount = 1;

	scanf_s("%d", &max);

	do
	{
		if (iCount % 2 == 0)
		{
			sum = sum + iCount++;
		}
		else
		{
			sum1 = sum1 + iCount++;
		}
	} while (iCount <= max);
	printf("1~n개까지의 짝수의 합:%d\n", sum);
	printf("1~n개까지의 홀수의 합:%d\n", sum1);
	printf("1~n개까지의 짝수 홀수의 합은:%d\n", sum + sum1);
	}