#include <stdio.h>

int main(void)
{
	int icount;
	int j = 0;
	{
		for (icount = 0; icount <= 100; icount++)
			j += icount;
			printf("1~100������ ��:%d\n",j);
	}
}