#include<stdio.h>
#include<conio.h>
//반대로 피라미드
void main()
{
	for (int sum = 0; sum < 5; sum++)
	{
		for (int sum1 = 0; sum1 < sum; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 < 2*(4-sum)-1 ; sum2++)
		{
			printf("*");
		}printf("\n");
	}_getch();
}