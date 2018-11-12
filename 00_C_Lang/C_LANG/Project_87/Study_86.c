#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void main()
{
	int arr[5], x;
	float farr[5];
	double darr[5];
	printf("\t\t Integer\t\tFloat\t\t Double");
	for (x = 0; x < 5; x++)
	{
		printf("\nElement %d:\t%d\t\t%d\t\t%d",
			x, &arr[x], &farr[x], &darr[x]);
	}
}