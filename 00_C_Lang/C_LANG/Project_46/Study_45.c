#include<stdio.h>
extern int a;
void func()
{
	a = 5;
}
int a;
void main()
{
	printf("%d\n", a);
	func();
	a = 10;
	printf("%d\n", a);
}