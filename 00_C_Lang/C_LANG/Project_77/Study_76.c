#include<stdio.h>
#include<conio.h>
//forÁ¦¾î¹®
//void main()
//{
//	int i;
//	for (i = 1; i <= 100; i++)
//		printf("%d", i);
//}

//void main()
//{
//	int i;
//	for (i = 1; i <= 100; i++)
//	{
//		if (i % 2 == 0)continue;
//		printf("%d", i);
//	}
//}

void main()
{
	int i;
	for (i = 1; i <= 100; i++)
	{
		if (i == 51)break;
		printf("%d",i);
	}
}