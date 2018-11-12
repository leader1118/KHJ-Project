#include<stdio.h>

int main()
{
	int a = 5;
	int b = 6;
	int c = 5;
	int d = 1;
	int x;
	x = a < b || a < c && c < d;
	printf("x is : %d", x);
	x = (a < b || a < c) && c < d;
	printf("\n x is : %d", x);

}