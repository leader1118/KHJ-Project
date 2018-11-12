#include <stdio.h>
#include<conio.h>
void main()
{
	int sum = 0;
	int iCount = 1;
	int max = 0;
	int sum1 = 0;

	scanf_s("%d", &max);
	do
	{
		if (iCount % 2 == 0) {
			sum = sum + iCount;
		}
		else 
		{
			sum1 += iCount;
		}
	} while (iCount++ < max);
	printf("%d\n", sum);
	printf("%d\n", sum1);
	_getch();
}