#include<stdio.h>
#include<conio.h>
//반대로 삼각형
void main()
{
	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 5-i-1; k++)
		{
			printf(" ");
		}
		for (int j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	_getch();
}