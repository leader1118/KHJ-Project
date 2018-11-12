#include <stdio.h>
#include <conio.h>
//피라미드
void main()
{
	for (int sum = 0; sum < 5; sum++)
	{
		for (int sum1 = 0; sum1 < 5-sum-1; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 <= sum*2; sum2++)
		{
			printf("*");
		}
	printf("\n");
	}
_getch();
}