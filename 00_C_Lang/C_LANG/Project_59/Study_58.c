#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void main()
{
	char*pCharPoint = 0;
	int iCount = 0;
	pCharPoint = (char*)malloc(sizeof(char) * 100);
	do
	{
		pCharPoint[iCount++] = _getche();
	} while (pCharPoint[iCount - 1] != '\r');

	//\n,\r

	pCharPoint[iCount + 1] = 0;
	printf("\n0x%08x번지:%s", pCharPoint, pCharPoint);
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		printf("\n0x%08x번지:%c", pCharPoint + iCnt, *(pCharPoint + iCnt));
	}
	free(pCharPoint);
}