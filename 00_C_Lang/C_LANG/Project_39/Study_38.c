#include<stdio.h>
#include<conio.h>
//�ݴ�� �ﰢ��
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