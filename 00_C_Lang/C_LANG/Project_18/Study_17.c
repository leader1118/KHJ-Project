#include <stdio.h>

void main()
{
	int a;
	{
		int b;
		a = 5;
		b = 10;
		printf("%d %d", a,b);
	}
	a = 10;
	int b=0;
	printf("%d %d", a,b);
}