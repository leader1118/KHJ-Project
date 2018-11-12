//�� ����(Quick Sort)
/*�� ������ ������� ������� ������ �ذ��ϴ� �˰���
�ǹ� ���� �����Ͽ� �ǹ� ������ ���� ������ ��������
������ ū ������ ���������� ���� �Ŀ� �̵� ���̿�
�ǹ��� ��ġ��Ű�� ������ �̿����� �ǹ����� ���� ������ ��� ȣ��� �����ϰ�
�ǹ����� ū ���鵵 �籸ȣ��� ���� �ϴ� ����̴�

���� �� �����δ� �� ������ ��� ��Ҹ� �ǹ����� �����ϳĿ� ���� ���ɿ� ���̰� �����.
���� ��ü ����� �߰� ������ ��Ҹ� ���� �ϸ���� ȣ�⿡�� �ݾ������� ������ �ϰԵǾ� ���� ������ �����Ѵ�
�ݴ�� ���� ���� ���̳� ���� ū���� �ǹ����μ����ϸ� �־��� ������ �����Ѵ�*/

#include <stdio.h>
#include<conio.h>

#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a�� b�� ��ȯ


int *origin;
int on;

void QuickSort(int *base, int n);
void ViewArr(int *arr, int n);
int main(void)
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
	origin = arr;
	on = 10;
	ViewArr(arr, 10);
	QuickSort(arr, 10);
	ViewArr(arr, 10);
	_getch();
	return 0;
}

void PrintSpace(int n);
void QuickSort(int *base, int n)
{
	int pivot = 0; // �ǹ��� ��ġ ����ϴ� ����
	int left = 0, right = 0; // �ǹ����� ū ���� ���� ���� ��ġ�� ã������ ����

	if (n <= 1)
	{
		return;
	}

	left = 0;
	right = n;

	//�� ��Ʈ�� �ǹ����� ���� ������ �������� �̵���Ű�� �ǹ����� ū ������ �������� �̵����Ѽ�
	//���� ����� ū ���� ���̿� �ǹ��� ������ ���� �⺻ �����Դϴ�.
	//�׸��� �� �Ŀ� ���� ������ �ִ� �迭�� ��������� �ٽ� �����ϰ�
	//ū ������ �ִ� �迭�� ��������� �ٽ� �����ϴ� �˰����Դϴ�. 
	while (1)
	{
		//���ʿ� �ǹ�(�ε��� 0�� �ִ� ����)���� ū ���� ���� ������ left�� �̵��մϴ�.
		//for�� �� ���� left�� 1 �����ϸ鼭 ����ϴ� ������ ������ ���� ���� ��ġ���� �����ϱ� ���ؼ��Դϴ�.
		for (left++; (left<n) && (base[0] >= base[left]); left++);
		//���ʿ� �ǹ�(�ε��� 0�� �ִ� ����)���� ���� ���� ���� ������ right�� �̵��մϴ�.
		for (right--; (right>0) && (base[0]<base[right]); right--);

		//���� left�� right���� �۴ٸ� �ǹ��� ������ �� ���� ���� ū ������ �ڿ� ������ ��ȯ�մϴ�.
		if (left<right)
		{
			SWAP(base[left], base[right]);
			PrintSpace(base - origin);
			ViewArr(base, n);
		}
		//�׷��� �ʴٸ� �ǹ��� �߽����� ���� ����� ū ������ �и� �۾��� ���� ���Դϴ�.
		else
		{
			break;
		}
	}
	//���� �ǹ��� ���� ����� ū ���� ���̷� �����ϴ�.
	SWAP(base[0], base[right]);
	PrintSpace(base - origin);
	ViewArr(base, n);

	//�ǹ����� ���� ������ �ִ� ������ ��� ȣ��� �����մϴ�.
	QuickSort(base, right);
	//�ǹ����� ū ������ �ִ� ������ ��� ȣ��� �����մϴ�.
	QuickSort(base + left, n - left);
}
void PrintSpace(int n)
{
	int i = 0;
	for (i = 0; i<n; i++)
	{
		printf("   ");
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
