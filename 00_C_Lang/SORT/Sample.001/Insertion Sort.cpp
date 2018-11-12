//���� ����(Insertion Sort)
/*���� ���� �˰����� ���������� ���� ������ ���� ������ ������� �����ϴ� �˰����̴�.
�̸� ���� ���ο� ������ �����ϴ� ������ ���Ҹ� ������ �̵��ϸ鼭 �ڽź��� ����
��Ҹ� ã�� ������ �̵��ϸ鼭 �ڸ��� ��ȯ�Ѵ�*/
#include <stdio.h>
#include<conio.h>

#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a�� b�� ��ȯ

void InsertionSort(int *base, int n);
int main(void)
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
	InsertionSort(arr, 10);
	_getch();
	return 0;
}
void ViewArr(int *arr, int n);
void InsertionSort(int *base, int n)
{
	int i, j;

	ViewArr(base, n);//���� ���� ���
	for (i = 1; i < n; i++)//������ ������ Ȯ���� �����ϴ�.
	{
		for (j = i; j > 0; j--)
		{
			if (base[j - 1] > base[j])//���� ���Ұ� �� ũ��
			{
				SWAP(base[j - 1], base[j]);//��ȯ
				ViewArr(base, n);//���� ���
			}
			else
			{
				break;
			}
		}
	}
}

void ViewArr(int *arr, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%2d ", arr[i]);
	}
	printf("\n");
}
