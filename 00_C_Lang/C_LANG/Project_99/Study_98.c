#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define USE_ARRAY

USE_ARRAY
int Data[20][20];

void MagicSquare(int iSize)
{
	int iWidth, iHeight;
	int suja;
	int iRow = 0;
	int iCol = (iSize - 1) / 2;
	Data[0][iCol] = 1;

	for (suja = 2; suja <= iSize * iSize; suja++)
	{
		if (iRow == 0)
		{
			iHeight = iSize - 1;
		}
		else
		{
			iHeight = iRow - 1;
		}
		if (iCol == iSize - 1)
		{
			iWidth = 0;
		}
		else
		{
			iWidth = iCol + 1;
		}
		if (Data[iHeight][iWidth] == 0)
		{
			iRow = iHeight, iCol = iWidth;
		}
		else
		{
			iRow++;
		}
		Data[iRow][iCol] = suja;
	}
}
void main()
{
	int iSize;

	for (;;)
	{
		printf("마방진 크기(3~19사이 홀수)....?");
		scanf_s("%d", &iSize);
		if (iSize >= 3 && iSize < 20)
		{
			break;
		}
		MagicSquare(iSize);

		for (int iRow = 0; iRow < iSize; iRow++)
		{
			for (int jCol = 0; jCol < iSize; jCol++)
			{
				printf("%4d",Data[iRow][jCol]);
			}
		}
		printf("\n");
	}_getch();
}
