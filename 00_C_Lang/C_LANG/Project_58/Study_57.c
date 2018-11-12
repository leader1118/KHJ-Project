#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void main()
{
	int *pPointArray = (int*)malloc(sizeof(int) * 10);
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		pPointArray[iCnt] = iCnt * 10;
		printf("\n0x%08x¹øÁö: %d", pPointArray[iCnt], *(pPointArray + iCnt));
	}
	free(pPointArray);
}
