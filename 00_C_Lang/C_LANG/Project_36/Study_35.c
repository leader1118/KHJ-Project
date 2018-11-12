#include <stdio.h>
// 삼각형 만들기
void main()
{
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}