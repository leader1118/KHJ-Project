#include<stdio.h>

void main()
{
	int sum = 0;
	int iCount = 1;
	int max = 0;

	scanf_s("%d", &max);

	while (iCount <= max)
	{
		sum = sum + iCount;
		iCount++;
	}
	printf("%d", sum);
}


