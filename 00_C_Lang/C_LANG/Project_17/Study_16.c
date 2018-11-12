#include<stdio.h>
void main()
{
	int count = 0;
	printf("Out,count=%d", count);
	{
		int count = 99;
		printf("In,count=%d",count);
	}
	printf("Out,count=%d", count);
}