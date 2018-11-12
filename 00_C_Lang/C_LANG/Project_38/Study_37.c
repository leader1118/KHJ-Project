#include<stdio.h>
#include<conio.h>
//¹ØÀ¸·Î »ï°¢Çü
void main()
{
    for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5-i; j++)
		{
			printf("*");
		}
		printf("\n");
	}_getch();
}