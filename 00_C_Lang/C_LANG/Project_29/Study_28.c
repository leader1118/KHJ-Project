#include<stdio.h>
#include<conio.h>

void main()
{
	int sum = 0;

	for (int i = 0; i <= 100; i++)
	{
		if (i % 2 == 0)
		{
			sum = sum + i;
		}
	}printf("¦���� ��:%d", sum);
	_getch();
}