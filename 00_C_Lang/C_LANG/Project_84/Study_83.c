#include<stdio.h>
#include<conio.h>
//Call by reference

//void func(int data[])
//{
//	data[0] = 10;
//}
//void main()
//{
//	int i;
//	int var[10] = { 1,2,3,4,5,6,7,8,9,0 };
//
//	func(var);
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d\n", var);
//	}
//}
//func함수를 호출할 때 var이란 변수를 인수로
//func함수에서는 data라는 인수로 배열을 전달


//Call by value

void func(int data)
{
	data = 10;
}
void main()
{
	int var = 1;
	func(var);
	printf("%d\n", var);
}
//main 함수에는 var이란 변수가
//그 변수에 초기값으로 1을 준 다음 func를 호출했는데
//인수로 var이란 변수를 주었음