#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//?
void draw(int row, int col);
void main()
{
	int row=0;
	int col=0;

	printf("행렬의 차원을 입력 합니다.\n");
	printf("x=");
	scanf_s("%d",&row);
	printf("y=");
	scanf_s("%d",&col);

	draw(row, col);
}
void draw(int row, int col)
{
	int temp = col;

	for (; row > 0; col--)
	{
		printf("X");
		col = temp;
		printf("\n");
	}
}