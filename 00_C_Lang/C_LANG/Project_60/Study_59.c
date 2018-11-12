#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void main()
{
	int *IpPoint[10];
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		IpPoint[iCnt] = (int*)malloc(sizeof(int));
		*IpPoint[iCnt] = iCnt * 10;
		printf("\n0x%08x¹øÁö:%d", IpPoint + iCnt, *IpPoint[iCnt]);
	}
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		free(IpPoint[iCnt]);
	}
}