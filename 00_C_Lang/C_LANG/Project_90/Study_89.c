#include<stdio.h>
#define MAX 10

int Iargest(int x[], int y);

void main()
{
	int array[MAX], count;
	for (count = 0; count < MAX; count++)
	{
		printf("Enter Number:");
		scanf_s("%d", &array[count]);
	}
	printf("\n\nLargest value = %d", Iargest(array, MAX));
}
int Iargest(int x[], int y)
{
	int count, biggest = x[0];
	for (count = 0; count < y; count++)
	{
		if (x[count] > biggest)
			biggest = x[count];
	}
	return biggest;
}