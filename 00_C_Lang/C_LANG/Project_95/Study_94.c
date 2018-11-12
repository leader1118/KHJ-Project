#include<stdio.h>
//get () 함수를 이용한 문자열

//void main()
//{
//	char input[81], *ptr;
//	puts("Enter a line, then press Enter");
//	puts("Enter a blank line when done.");
//	while (*(ptr = gets(input)) != NULL)
//	{
//		printf("You enterd %s\n", input);
//	}
//}

void main()
{
	char letters[5];
	int i;
	for (i = 0; i < 5; i++)
	{
		letters[i] = getchar();
	}
	for (i = 4; i >= 0; i++)
	{
		putchar(letters[i]);
	}
}