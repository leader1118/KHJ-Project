#include<stdio.h>
#include<conio.h>
void main()
{
	int sum = 0;
	int sum1 = 0;
	int max = 0;
	int iCount = 1;

	scanf_s("%d", &max);

	do
	{
		sum = sum + iCount++;
	} while (iCount <= max);
	printf("1~N�� ������ ��:%d\n", sum);
	_getch();
}