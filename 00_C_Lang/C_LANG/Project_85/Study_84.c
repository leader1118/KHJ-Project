#include<stdio.h>
#include<conio.h>
// 다차원 배열

//void main()
//{
//	int a[2][3];
//	int i;
//	int j;
//
//	a[0][0] = 0; a[0][1] = 1; a[0][2] = 2;
//	a[1][0] = 1; a[1][1] = 2; a[1][2] = 3;
//
//	printf("\n[%d][%d]=%d", 0, 0, a[0][0]);
//	printf("\n[%d][%d]=%d", 1, 0, a[1][0]);
//	printf("\n[%d][%d]=%d", 0, 1, a[0][1]);
//	printf("\n[%d][%d]=%d", 1, 1, a[1][1]);
//	printf("\n[%d][%d]=%d", 0, 2, a[0][2]);
//	printf("\n[%d][%d]=%d", 1, 2, a[1][2]);
//	printf("\n[%d][%d]=%d", 0, 0, a[0][0]);
//}

void main()
{
	int i;
	int j;
	static int integer[2][3] = { 1,2,3,4,5 };

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("\n integer[%d][%d]=%d", i, j, integer[i][j]);
		}
	}
}