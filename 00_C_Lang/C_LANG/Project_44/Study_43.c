#include<stdio.h>
int a;
void func(void)
{
	a = 5;
}
void main()
{
	func();
	printf("%d\n", a);
	a = 10;
	printf("%d\n", a);
}