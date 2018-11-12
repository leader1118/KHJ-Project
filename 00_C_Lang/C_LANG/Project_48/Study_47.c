#include<stdio.h>
#include<conio.h>
void func()
{
	static int a = 0;
	a = a + 1;
	printf("%d\n", a);
}
void main()
{
	func();
	func();
	func();

	_getch();
}