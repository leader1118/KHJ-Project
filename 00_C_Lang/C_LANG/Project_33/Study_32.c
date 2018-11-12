#include<stdio.h>

void main()
{
	int sum = 0;
	int max = 0;
	int iCount = 1;

	do
	{
		sum = sum + iCount++;
	} while (iCount <= 100);
	printf("1~100까지의 합:%d\n", sum);
}