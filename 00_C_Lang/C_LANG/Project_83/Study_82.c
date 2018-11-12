#include<stdio.h>
#include<conio.h>
//1차원 배열

//int index, arr[10];
//
//void main()
//{
//	for (index = 0; index < 10; index++)
//	{
//		scanf_s("%d", &arr[index]);
//	}
//	for (index = 0; index < 10; index++)
//	{
//		printf("%d:%d\n", index, arr[index]);
//	}
//}

//void main()
//{
//	int i, integer[2];
//	char ch[2];
//	integer[0] = 1;
//	integer[1] = 2;
//	ch[0] = 'a'; ch[1] = 'b';
//
//	for (i = 0; i < 2; i++)
//	{
//		printf("\n%d", integer[i]);
//	}
//	for (i = 0; i < 2; i++)
//		printf("\n%c", ch[i]);
//	_getch();
//}

#include<stdio.h>

void main()
{
	int i;
	static int integer[5];
	static char ch[5];
	static float f[5];

	for (i = 0; i < 5; i++)
	{
		printf("%3d", integer[i]);
		printf("\n");
	}
	for (i = 0; i < 5; i++)
	{
		printf("%3c",ch[i]);
		printf("\n");
	}
	for (i = 0; i < 5; i++)
	{
		printf("%5.3f", f[i]);
	}
	_getch();
}