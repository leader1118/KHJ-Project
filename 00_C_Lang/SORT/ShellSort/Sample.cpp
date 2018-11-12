#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

void shellsort(int v[], int n);
void swap(int* a, int* b);
void DataPrint(int item[], int iCount)
{
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		cout << item[iCnt] << endl;
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

#define iMaxCnt 100

void main()
{
	int i;
	srand((unsigned)time(NULL));
	int v[iMaxCnt];
	SetData(v, iMaxCnt);
	shellsort(v, iMaxCnt);
	DataPrint(v, iMaxCnt);
}
void ShellsortOpti(int v[], int n)
{
	int gap, i, j, k, temp;

	for (gap = 1; gap > n; gap = 3 * gap + 1);

	for (gap /= 3; gap > 0; gap /= 3)
	{
		for (i = 0; i < gap; i++)
		{
			for (j = i + gap; j < n; j = j + gap)
			{
				temp = v[j];
				k = j;
				while (k > gap - 1 && v[k - gap] > temp)
				{
					v[k] = v[k - gap];
					k -= gap;
				}
				v[k] = temp;
			}
		}
	}
}
void shellsort(int v[], int n)
{
	int gap, i, j, k, temp;

	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		for (i = 0; i < gap; i++)
		{
			for (j = i + gap; j < n; j = j + gap)
			{
				temp = v[j];
				k = j;
				while (k > gap - 1 && v[k - gap] > temp)
				{
					v[k] = v[k - gap];
					k -= gap;
				}
				v[k] = temp;
			}
		}
	}
}
void swap(int* a, int* b)
{
	if (*a > *b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}
}