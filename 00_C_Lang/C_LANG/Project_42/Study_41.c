#include<stdio.h>
#include<conio.h>
//다이아몬드 완성 .. 휴
void main()
{
	for (int sum = 0; sum < 4; sum++)
	{
		for (int sum1 = 0; sum1 < 4-sum; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 <= sum*2; sum2++)
		{
			printf("*");
		}
	printf("\n");
	}
	for (int sum = 0; sum < 5; sum++)
	{
		for (int sum1 = 0; sum1 < sum; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 < 2 * (5 - sum) - 1; sum2++)
		{
			printf("*");
		}
		printf("\n");
	}
_getch();
}