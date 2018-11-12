#include<stdio.h>
unsigned int f,x;
unsigned int fact(unsigned int a);
main()
{
	printf("Enter number(1-8):");
	scanf_s("%d", &x);
	printf("%d factprial equals %d", x, fact(x));
}
unsigned int fact(unsigned int a)
{
	if (a == 1)
	{
		return 1;
	}
	else
	{
		a *= fact(a - 1);
		return a;
	}
}