#include <stdio.h>

void main()
{
	int i;
	int j=0;
	int k;

	{
		scanf_s("%d", &k);
		for (i = 0; i <= k; i++)
			j += i;
		
		printf("%d", j);
	}
}