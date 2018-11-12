#include<stdio.h>
#include<stdlib.h>
//동적 할당

//void main()
//{
//	char count, *ptr, *p;
//	ptr = (char *)malloc(35 * sizeof(char));
//	if (ptr == NULL)
//	{
//		puts("Memory allocation eroor.");
//		exit(1);
//	}
//	p = ptr;
//	for (count = 65; count < 91; count++)//아스키 코드 A~Z
//	{
//		*p++ = count;
//		*p = '\0';
//		puts(ptr);
//	}
//}

void main()
{
	unsigned char x;
	for (x = 65; x < 91; x++)
	{
		printf("ASCII code %d is Character:%c\n",x, x);
	}
}