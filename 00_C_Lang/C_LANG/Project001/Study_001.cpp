#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void swap(int *a, int *b)// �Լ�
{
	int j = *a;
	int k = *b;
	
	*a = k;
	*b = j;
}

void main() // ���� �Լ�
{
	int a = 3;
	int b = 5;
	swap(&a,&b);
	printf("%d,%d", a, b);
}