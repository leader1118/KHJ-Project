#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	system("cls");

	char *pArray[6];
	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		pArray[iCnt] = (char*)malloc(sizeof(char) * 4);
	}
	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		for (int jCnt = 0; jCnt < 3; jCnt++)
		{
			pArray[iCnt][jCnt] = 65 + iCnt * 3 + jCnt;
		}
		pArray[iCnt][3] = 0;
	}
	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		printf("\n");
		printf("[%d]=%s", iCnt, pArray[iCnt]);
	}
	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		free(pArray[iCnt]);
	}
	_getch();
}