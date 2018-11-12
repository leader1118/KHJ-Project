#include<stdio.h>

int main(void)
{
	int val1 = 15;
	int val2 = 28;
	int logicAnd;
	int bitAnd;

	logicAnd = val1 && val2;
	bitAnd = val1 & val2;
	printf("%d\n",val1&val2);
}