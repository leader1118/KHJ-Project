#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	int iValue[3][2] = { {10,20},{30,40},{50,60} };
	for (int iCnt = 0; iCnt < 3; iCnt++)
	{
		printf("\n*(iValue+%d):%p", iCnt, *(iValue + iCnt));
		printf("\t\tiValue[%d]:%p", iCnt, iValue[iCnt]);
	}
	printf("\n");
	for (int iCnt = 0; iCnt < 3; iCnt++)
	{
		for (int jCnt = 0; jCnt < 2; jCnt++)
		{
			printf("\n*(*iValue+%d)+%d):%d", iCnt, jCnt, *(*(iValue + iCnt) + jCnt));
			printf("\t\t *(iValue[%d]+%d):%d", iCnt, jCnt, *(iValue[iCnt] + jCnt));
		}
	}
	_getch();
}