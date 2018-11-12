#include<stdio.h>

void main()
{
	int k = 0;
	int j = 0;
	
	for (int i = 0; i <= 100; i++)
	{
		if (i % 2 == 0)
		{
			k = k + i;
		}
		else
		{
			j = j + i;
		}
	}
	printf("%d\n", k);
	printf("%d\n", j);
	printf("%d",k+j);
}