#include<stdio.h>
#include<conio.h>
// 다이아몬드 
void main()
{
	int Start = 6;
	int Count = 1;
	
	for (int i = 1; i <= 5; i++)
	{
		for (int space = 1; space <= 11; space++)
		{
			if (space == Start)
			{
				for (int j = 1; j <= Count * 2; j++)
					printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
		Start--; Count++;
	}
	Count--;
	Start++;

	for (int i = 1; i <= 4; i++)
	{
		Start++;
		Count--;

		for (int spaceb = 1; spaceb <= 11; spaceb++)
		{
			if (spaceb == Start)
				for (int j = 1; j <= Count * 2; j++)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}printf("\n");
	}
	_getch();
}