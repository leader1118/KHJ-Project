#include<stdio.h>
//다중 배열 포인터
void main()
{
	int c;
	int arr[9][9];
	printf("input num\n");
	scanf_s("%d",&c);

	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			arr[i - 1][j - 1] = (i)*(j);
		}
	}
	for (int z = 0; z <= 8; z++)
		printf("\n%d*%d=%d", c, z + 1, *(*(arr + c - 1) + z));
}