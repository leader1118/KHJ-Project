#include<stdio.h>
#include<conio.h>

void main()
{
	int a = 4;
	switch (a)
	{
	case 1:
	{
		printf("One\n");
	}
	case 2:
	{
		printf("Two\n");
	}
	case 3:
	{
		printf("Three\n");
	}
	default:
	{
		printf("Another value\n");
		break;
	}
	}
}