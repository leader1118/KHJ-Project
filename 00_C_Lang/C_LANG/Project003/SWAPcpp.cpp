#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void swap(int *a,int *b)
{
	int i = *a;//������ ��������
	*a = *b;
	*b = i;

}
void main()//�����Լ�
{
	int a = 0;//���� �ʱ�ȭ
	int b = 0;
	

	printf("\n�� �Է�: ");
	scanf("%d %d", &a, &b);

	swap(&a,&b);//�ּҰ����� ���� swap
		printf("���: %d %d", a, b);
		_getch();
}

