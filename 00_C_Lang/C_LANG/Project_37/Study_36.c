#include<stdio.h>
//»ï°¢Çü ¹Ý´ë·Î ¸¸µé±â
void main()
{
	int line = 0;
	scanf_s("%d", &line);
	//»ï°¢Çü
	for (int i = 0; i <= line; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("*");
		}printf("\n");
	}
	//¹ØÀ¸·Î »ï°¢Çü
	for (int i = 0; i <= line; i++)
	{
		for (int j = 0; j <= line-i; j++)
		{
			printf("*");
		}
	printf("\n");
	}
}