//���� ����(Bubble Sort)
/*�տ��� ���� �̿��ϴ� ������ ���� ���Ͽ� ��ġ�� ��ȯ�ϴ� ���� �ݺ��ϸ� ������
�ݺ��ϸ� ���� ū ���� �ǵڿ� ��ġ�Ѵ�.�׸��� ������ ������ 1 ������ �ٽ� �ݺ��ϸ�
������ ������ ������ 1�̸� ��� �ݺ��� �Ϸ�*/
#include <stdio.h>
#include<conio.h>

#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a�� b�� ��ȯ


void BubbleSort(int *base, int n);
int main(void)
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
	BubbleSort(arr, 10);
	_getch();
	return 0;
}
void ViewArr(int *arr, int n);
void BubbleSort(int *base, int n)
{
	int i, j;
	ViewArr(base, n);//���� ���� ���
	for (i = n; i>1; i--)//������ ������ ����� �����ϴ�.
	{
		for (j = 1; j<i; j++)
		{
			if (base[j - 1]>base[j])//���� ���Ұ� �� ũ��
			{
				SWAP(base[j - 1], base[j]);//��ȯ
				ViewArr(base, n);//���� ���
			}
		}
	}
}

void ViewArr(int *arr, int n)
{
	int i = 0;
	for (i = 0; i<n; i++)
	{
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

