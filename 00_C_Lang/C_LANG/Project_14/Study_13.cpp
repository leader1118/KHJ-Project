#include <stdio.h>
#define PI 3.14159

int main(void)
{
	int number = 5;
	float ouzo = 13.5;
	int cost = 31000;

	printf("The %d women drank %f glasses of ouzo.\n", number, ouzo);
	printf("The value of pi is %f.\n", PI);
	printf("���� �ȳ��ϼ���.\n");
	printf("%c%d\n", '$', cost);
	printf("If you want to printf percent...put character%%.\n");
	number = 1 + 3;
	printf("number=%d", number);


}