#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>

int main(int argc, char*argv[])
{

	FILE*fp;
	char c;
	if (argc == 1)//���ڰ� ������
	{
		printf("USAGE: %s filename(1)...filename(n)\n", *argv);
		return (1);
	}
	while (--argc > 0)//���ڰ� ������
		if ((fp = fopen(*++argv, "r")) == NULL)
		{
			printf("Error:Cannot open %s\n", *argv);
			continue;
		}
	printf("\n***%s***\n", argv);
	while ((c = getc(&fp)) != EOF)
		putchar(c);
	fclose(fp);
	_getch();
}