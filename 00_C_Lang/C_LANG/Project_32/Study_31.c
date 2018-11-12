#include<stdio.h>

void main()
{
	int sum = 0;
	int max = 0;
	int iCount = 1;

	scanf_s("%d", &max);

	while (iCount <= max)
	{
		sum = sum + iCount++;
	}
	printf("1~100까지의 합:%d\n", sum);
}