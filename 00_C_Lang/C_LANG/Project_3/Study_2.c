#include <stdio.h>

int main(void)
{
	printf("Type int has a size of %d bytes.\n", sizeof(int));
	printf("Type char has a size of %d bytes.\n", sizeof(char));
	printf("Type long has a size of %d bytes.\n", sizeof(long));
	printf("Type double has a size of %d bytes.\n", sizeof(double));
	printf("Type float has a size of %d bytes.\n", sizeof(float));
	printf("Type short has a size of %d bytes.\n", sizeof(short));

	return 0;
}