#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//#define MAX 10
//포인터 연산

//void main()
//{
//	int arr[MAX] = { 0,1,2,3,4,5,6,7,8,9 };
//	int *ptr, count;
//	ptr = arr;
//	
//	for (count = 0; count < MAX; count++)
//	{
//		printf("%d\n,*ptr++");
//	}
//	for (count = MAX - 1; count < MAX; count++)
//	{
//		printf("%d\n", *--ptr);
//	}
//}

void main()
{
	int arr[10] = { 0,1,2,3,4,5,6,7 };
	int i, *ptr, *ptr1;
	ptr = arr;
	ptr1 = &arr[5];
	
	printf("Difference:%d\n", ptr1 - ptr);
	printf("Compare:%d\n",ptr>ptr1);
	
	for (i = 0; i < 10; i++)
	{
		printf("%d\t", *ptr++);
	}
	_getch();
}