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
//func�Լ��� ȣ���� �� var�̶� ������ �μ���
//func�Լ������� data��� �μ��� �迭�� ����


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
//main �Լ����� var�̶� ������
//�� ������ �ʱⰪ���� 1�� �� ���� func�� ȣ���ߴµ�
//�μ��� var�̶� ������ �־���