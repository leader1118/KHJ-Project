#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void swap(int *a, int *b)// 함수
{
	int j = *a;
	int k = *b;
	
	*a = k;
	*b = j;
}

void main() // 메인 함수
{
	int a = 3;
	int b = 5;
	swap(&a,&b);
	printf("%d,%d", a, b);
}