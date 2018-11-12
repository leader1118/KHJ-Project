#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


//void main()
//{
//	size_t length;
//	char buf[80];
//	while (1)
//	{
//		puts("Enter a line of text");
//		puts("blank line terminates.");
//		gets(buf);
//		length = strlen(buf);
//		if (length != 0)
//		{
//			printf("%u caracters\n\n", length);
//		}
//		else
//		{
//			break;
//		}
//	}
//}

void main()
{
	char word[] = "Happy Birth day";
	char *great = "hello";
	int count = 0;
	while (word[count] != NULL)
	{
		count++;
		printf("Length =%d\n", count);
	}
	count = 0;
	while (great[count] != NULL)
	{
		count++;
		printf("Length=%d\n", count);
	}
}