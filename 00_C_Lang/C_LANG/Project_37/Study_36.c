#include<stdio.h>
//�ﰢ�� �ݴ�� �����
void main()
{
	int line = 0;
	scanf_s("%d", &line);
	//�ﰢ��
	for (int i = 0; i <= line; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("*");
		}printf("\n");
	}
	//������ �ﰢ��
	for (int i = 0; i <= line; i++)
	{
		for (int j = 0; j <= line-i; j++)
		{
			printf("*");
		}
	printf("\n");
	}
}