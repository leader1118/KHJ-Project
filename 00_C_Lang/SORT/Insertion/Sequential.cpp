#include<stdio.h>//printf���� scanf�� ����ϱ� ���� ���
#include<conio.h>//_getch()�� ����� ���� ���
#define SWAP(a,b) {int t; t=a; a=b; b=t;}//a��b�� ��ȯ

void SequenoeSort(int *base, int n); 
int main(void)//����
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1, }; // �迭 ���� �ʱ�ȭ
	SequenoeSort(arr, 10);//�Լ� ȣ��

	_getch();
	return 0;
}
void ViewArr(int *arr, int n); 
void SequenoeSort(int *base, int n)
{
	int i;
	int j;
	ViewArr(base, n); //���� ���� ���

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (base[i] > base[j])//���� ���Ұ� �� ũ��
			{
				SWAP(base[i], base[j]);//��ȯ
				ViewArr(base, n);//���� ���
			}
		}
	}

}
void ViewArr(int *arr, int n)// ���� ���� �迭 ���
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%2d\t", arr[i]);
	}
	printf("\n");
}