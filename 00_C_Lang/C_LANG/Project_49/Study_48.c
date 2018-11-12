#include <stdio.h>

int x = 1;
int y = 2;

void demo(void);
main()
{
	printf("Before:x=%d,y=%d\n", x, y);
	demo();
	printf("After:x=%d,y=%d\n",x,y);
}
void demo(void)
{
	int x = 88;
	int y = 99;
	printf("In demo():x=%d,y=%d\n", x, y);
}