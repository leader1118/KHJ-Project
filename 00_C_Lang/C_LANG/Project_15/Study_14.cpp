#include <stdio.h>

void main()
{
	char ch;
	ch = getchar();
	putchar(ch);

	putchar('S');
	putchar('\n');
	putchar('\007');
	putchar(getchar());
}