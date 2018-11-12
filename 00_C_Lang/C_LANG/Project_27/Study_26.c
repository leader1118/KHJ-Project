#include <stdio.h>
#include <conio.h>

void main()
{
	int sum = 0;
	int sum1 = 0;
	int iCount = 1;
	int max = 0;

	scanf_s("%d", &max);

	do
	{
		sum = sum + iCount;
		iCount++;
	} while (iCount<=max);
	printf("%d", sum);
}