#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void swap(int *a,int *b)
{
	int i = *a;//포인터 변수선언
	*a = *b;
	*b = i;

}
void main()//메인함수
{
	int a = 0;//변수 초기화
	int b = 0;
	

	printf("\n값 입력: ");
	scanf("%d %d", &a, &b);

	swap(&a,&b);//주소값에서 서로 swap
		printf("출력: %d %d", a, b);
		_getch();
}

