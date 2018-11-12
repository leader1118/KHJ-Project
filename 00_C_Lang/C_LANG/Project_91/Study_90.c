#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//행렬 예제(포인터)

void printf_array(int *num, int row, int col);

void main()
{
	int row;
	int col;
	int datd[100][100];
	int i;
	int j;

	printf("Enter the row and columm:");
	scanf_s("%d%d", &row, &col);

	if (row > 1000 || col > 1000)
	{
		printf("the values should be between 0 and 999\n");
		exit(1);
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			*(&data[0][0] + i * col + j) = (int)rand() % 100;
	}
	print_array((int*)data, row, col);
}

void printf_array(int *num, int row, int col)
{
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%3d", *(num + i * col + j));
			printf("\n");
		}
	}
}