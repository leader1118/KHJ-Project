//�� ����(Shell Sort)
/*�� ������ ���� ���� �˰����� �̿��ϴ� ���� ����̴�.
���� ���ݿ� �ִ� ���ҵ��� ���� ���� ������ �����ϴ� ���� 
�ݺ������� �ʱⰪ�� �迭�� ũ�� /2 �̸� ������ 1�ϋ�����
1/2�� ���̸鼭 �ݺ��Ѵ�*/
#include <stdio.h>
#include <conio.h>
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a�� b�� ��ȯ


int *origin;
int on;

void ShellSort(int *base, int n);
int main(void)
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
	origin = arr;
	on = 10;
	ShellSort(arr, 10);
	_getch();
	return 0;

}
void InsertionSort2(int *base, int size, int step);
void ViewArr(int *arr, int n);
void ShellSort(int *base, int size)
{
	int i, step;

	for (step = size / 2; step>0; step /= 2)//step�� ���� 1/2�� �ٿ�����.
	{
		printf("step:%d\n", step);
		for (i = 0; i<step; i++) //step ���ݿ� �ִ� ��ҵ��� ��������
		{
			InsertionSort2(base + i, size - i, step);
		}
	}
}

void InsertionSort2(int *base, int size, int step)
{
	int i, j;
	for (i = step; i<size; i += step)//���� ��� ���Ҵ� step �������� �̵�
	{

		for (j = i; j>0; j -= step)//step �������� ������ �̵�
		{
			if (base[j - step]>base[j])//������ �� Ŭ ��
			{
				SWAP(base[j - step], base[j]);//��ȯ
				ViewArr(origin, on);
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
	for (i = 0; i<n; i++)
	{
		printf("%2d ", arr[i]);
	}
	printf("\n");
}
