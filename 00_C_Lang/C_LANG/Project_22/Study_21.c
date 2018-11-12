#include <stdio.h>

int main(void)
{
	int icount = 1;
	int sum1 = 0;
	
	while (icount <= 100)
	{
		sum1 = sum1 + icount;
		icount++;
	}
	printf("1~100까지의 합:%d", sum1);
	
	return 0;
}