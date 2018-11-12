#include <stdio.h>

void main()
{
	int sum = 0;
	int iCount = 1;

	while (iCount <= 100)
	{
		sum = sum + iCount++;
	}
	printf("1~100까지의 합:%d\n", sum);
}