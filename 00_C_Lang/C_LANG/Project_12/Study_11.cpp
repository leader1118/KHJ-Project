#include<stdio.h>

int main(void)
{
	unsigned char fourBitVal1 = 0x05, fourBitVal2 = 0x07;
	
	unsigned char eightBitVal;
	eightBitVal = fourBitVal1 << 4;
	eightBitVal |= fourBitVal2;

	printf("%x,%x_>%x\n", fourBitVal1, fourBitVal2, eightBitVal);

	return 0;
}