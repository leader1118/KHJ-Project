#include<stdio.h>
#include<conio.h>

void swap(int *a,int *b)
{
	int i = *a;
	int j = *b;

	*a = j;
	*b = i;
}
void main()
{
	int a = 3;
	int b = 5;

	swap(&a, &b);
	printf("%d %d", &a, &b);
}