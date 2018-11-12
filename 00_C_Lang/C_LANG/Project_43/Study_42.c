#include<stdio.h>
#include<conio.h>

//입력 받은 개수로 다이아 몬드 만들기
void main()
{
	int line = 0;

	scanf_s("%d", &line);

	for (int sum = 0; sum < line-1; sum++)
	{
		for (int sum1 = 0; sum1 < line-sum-1; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 <= sum*2; sum2++)
		{
			printf("*");
		}
	printf("\n");
	}
	for (int sum = 0; sum < line; sum++)
	{
		for (int sum1 = 0; sum1 < sum; sum1++)
		{
			printf(" ");
		}
		for (int sum2 = 0; sum2 < 2*(line-sum)-1; sum2++)
		{
			printf("*");
		}
	printf("\n");
	}
	_getch();
}