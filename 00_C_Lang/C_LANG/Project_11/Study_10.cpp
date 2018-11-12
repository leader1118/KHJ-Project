#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 5;
	int c;
	
	c = b > a ? b : a;

	printf("%d\n",c);
	printf("%d\n", b > a ? b : a);

	
}