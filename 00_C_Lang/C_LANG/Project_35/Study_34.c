#include<stdio.h>

void main()
{
	int sum = 0;
	int sum1 = 0;
	int max = 0;
	int iCount = 1;

	scanf_s("%d", &max);

	do
	{
		if (iCount % 2 == 0)
		{
			sum = sum + iCount++;
		}
		else
		{
			sum1 = sum1 + iCount++;
		}
	} while (iCount <= max);
	printf("1~n�������� ¦���� ��:%d\n", sum);
	printf("1~n�������� Ȧ���� ��:%d\n", sum1);
	printf("1~n�������� ¦�� Ȧ���� ����:%d\n", sum + sum1);
	}