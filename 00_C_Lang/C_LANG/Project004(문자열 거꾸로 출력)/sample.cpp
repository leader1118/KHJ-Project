#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<conio.h>

void main()
{
	int i;
	int j;
	char str[30];

	scanf("%s", str);
	j = strlen(str);

	for (i = j - 1; i >= 0; i--)
	{
		printf("%c", str[i]);
	}
	_getch();
}