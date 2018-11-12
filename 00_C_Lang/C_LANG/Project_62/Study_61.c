#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	system("cls");
	int *pPtr;
	int **ppPtr;
	int num = 10;
	pPtr = &num;
	//포인터의 메모리 주소는 일반포인트에 저장 불가하며
	//반드시 이중포인터에 저장해야 한다.
	ppPtr = &pPtr;//pPtr의 주소 저장
	printf("%d\n", **ppPtr);//ppPtr의 메모리 주소에 접근
	
	int **ppPoint = 0;
	ppPoint = (int**)malloc(sizeof(int) * 10);
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		ppPoint[iCnt] = (int*)malloc(sizeof(int) * 10);
	}

	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		for (int jCnt = 0; jCnt < 10; jCnt++)
		{
			ppPoint[iCnt][jCnt] = iCnt * 10 + jCnt;
		}
	}
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		printf("\n");
		for (int jCnt = 0; jCnt < 10; jCnt++)
		{
			printf("[%d,%d]=%d", iCnt, jCnt, ppPoint[iCnt][jCnt]);
			printf("[%d,%d]=%d", iCnt, jCnt, *(ppPoint[iCnt] + jCnt));
		}
	}
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		free(ppPoint[iCnt]);
	}
	free(ppPoint);
}