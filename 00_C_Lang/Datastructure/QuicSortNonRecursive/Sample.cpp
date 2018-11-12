#include "Sample.h"

void qsort(int a[], int n)
{
	int p, t;
	int i, j;
	int l, r;

	InitStack();

	l = 0;
	r = n - 1;

	StackPush(r);
	StackPush(l);

	while (!IsStatkEmpty())
	{
		l = StackPop();
		r = StackPop();

		if (r - l + 1 > 1)
		{
			//�������� ::���� �ִ� ������ ���� ������ 1�� �̻��� ���
			p = a[r];
			i = l - 1;
			j = r;

			while (1)
			{
				while (a[++i] < p);
				while (a[--j] > p);
				if (i >= j)break;
				Swap(&a[i], &a[j]);
			}
			
			//pivot�� i���� ��ȯ
			Swap(&a[i], &a[r]);

			StackPush(r);  //������ ������ ������ ��
			StackPush(i+1);  //������ ������ ���� ��
			StackPush(i-1);  //���� ������ ������ ��
			StackPush(l);  // ���� ������ ���� ��
		} // if
	}// while
}
void DataPrint(int item[], int iCount)
{
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		std::cout << item[iCnt] << std::endl;
	}
}
void SetData(int item[], int iCount)
{
	srand((unsigned int)time(NULL));
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		item[iCnt] = rand() % iCount;
	}
}
void main()
{
	srand((unsigned)time(NULL));
	int data[MAX_NUM];
	for (int i = 0; i < MAX_NUM; i++)
	{
		data[i] = rand() % MAX_NUM;
		StackPush(data[i]);
		QueuePush(data[i]);
	}
	// ���� ������
	printf("\n���� ������");
	DataPrint(data, MAX_NUM);

	//int Size = sizeof(data)/sizeof(data[0]);  
	printf("\n���� ������");
	for (int i = 0; i<MAX_NUM; i++)
	{
		printf(" %d", StackPop());
	}
	//printf("%c",'\n');
	printf("\nť ������");
	for (int i = 0; i<MAX_NUM; i++)
	{
		printf(" %d", QueuePop());
	}
	printf("%c", '\n');

	qsort(data, MAX_NUM);

	printf("\n�� ���� ������");
	DataPrint(data, MAX_NUM);
}