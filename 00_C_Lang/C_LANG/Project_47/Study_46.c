#include<stdio.h>

void func()
{
	int a = 0;
	a = a + 1;
	printf("%d\n", a);
}
void main()
{
	func();
	func();
	func();
}