#include<stdio.h>
#include<stdlib.h>

void main()
{
	int item[100];
	int	count, a;
	printf("How many numbers?");
	scanf_s("%d", &count);
	for (a = 0; a < count; a++)
	{
		scanf_s("%d", &item[a]);
		printf("%5.5f", mean(item, count));
	}
	
}

//double mean(int item[], int n)
//{
//	int total = 0;
//	for (int i = 0; i < n; i++)
//	
//		total += item[i];
//	
//	return double (total/n);
//}