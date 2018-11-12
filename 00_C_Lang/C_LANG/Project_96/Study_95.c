#include<stdio.h>

void main()
{
	char lname[81],fname[81];
	int count, id_num;
	puts("Enter last name.first name, ID number");
	puts("separated by spaces, then press Enter");
	count =
		scanf_s("%s%s%d", lname, fname, &id_num);
	printf("%d items entered: %s %s %d", count, fname, lname, id_num);
}