#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void main()
{
	int *pPoint = (int*)malloc(sizeof(int));
	*pPoint = 100;
	printf("%0x����:%d\n", pPoint + 0, *(pPoint + 0));
	free(pPoint = 100);
	
}