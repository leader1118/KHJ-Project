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
	//�������� �޸� �ּҴ� �Ϲ�����Ʈ�� ���� �Ұ��ϸ�
	//�ݵ�� ���������Ϳ� �����ؾ� �Ѵ�.
	ppPtr = &pPtr;//pPtr�� �ּ� ����
	printf("%d\n", **ppPtr);//ppPtr�� �޸� �ּҿ� ����
	
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