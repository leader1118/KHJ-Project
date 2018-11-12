#include<stdio.h>

void main()
{
	int sum = 0;
	for (int i = 0; i <= 100; i++)
	{
		sum += i;
	}
	printf("1~100까지의 합:%d\n",sum);
}