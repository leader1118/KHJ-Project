#include <stdio.h>

int main(void)
{
	int a = 2 != 4 && 5 > 3;
	int b = !1 || !0;

	printf("%d\n", a);
	printf("%d\n", b);
}