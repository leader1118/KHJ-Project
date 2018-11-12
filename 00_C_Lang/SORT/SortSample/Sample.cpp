#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
bool swap(int* a, int* b)
{
	if (*a > *b)
	{
		int t = *a;
		*a = *b;
		*b = t;
		return true;
	}
	return false;
}
void SelectionSort(int item[], int count)
{
	for (int a=0; a<count; a++)
	{
		for (int b = a + 1; b < count; b++)
		{
			swap(&item[a], &item[b]);
		}
	}
}
void BubbleSort(int item[], int count)
{
	for (int a = 0; a < count - 1; a++)
	{
		bool bFlag = false;
		for (int b = 0; b < count - a - 1; b++)
		{
			if (swap(&item[a], &item[b]))
			{
				bFlag = true;
			}
		}
		if (bFlag == false)
			break;
	}
}
void InsertionSort(int item[], int count, int iStart = 1, int iStep = 1)
{
	for (int a = iStart; a < count; a += iStep)
	{
		int temp = item[a];
		int b = a - iStep;
		while (b >=0 && item[b] > temp)
		{
			item[b + iStep] = item[b];
			b -= iStep;
		}
		item[b + iStep] = temp;
	}
}
void shellsort(int item[], int n)
{
	int k = 4;
	while (k>1)
	{
		k = k / 2;

		for (int s = 0; s < k; s++)
		{
			InsertionSort(item, n, s, k);
		}
	}
}
void DataPrint(int item[], int iCount)
{
	//return;
	for (int t = 0; t < iCount; t++)
	{
		if (t % 20 == 0)
		{
			cout << " ";
		}
		cout << item[t]<<" ";
	}
}
void Merge(int item[], int iStart, int iEnd, int iMiddle)
{
	vector<int>itemList;
	int i = iStart;
	int j = iMiddle + 1;


	while (i <= iMiddle && j <= iEnd)
	{
		if (item[i] < item[j])
		{
			itemList.push_back(item[i++]);
		}
		else
		{
			itemList.push_back(item[j++]);
		}
	}
	while (i <= iMiddle)itemList.push_back(item[i++]);
	while (j <= iEnd)itemList.push_back(item[j++]);

	int copy = 0;
	for (int k = iStart; k <= iEnd; k++)
	{
		item[k] = itemList[copy++];
	}
}
void MergeSort(int item[], int iStart, int iEnd)
{
	if (iStart < iEnd)
	{
		int iMiddle = (iStart + iEnd) / 2;

		MergeSort(item, iStart, iMiddle);
		MergeSort(item, iMiddle + 1, iEnd);

		Merge(item,iStart, iEnd, iMiddle);
	}
}
void QuickSort(int item[], int iStart, int iEnd)
{
	int iPivot = item[iStart];
	int iBeginStart = iStart;
	int iBeginEnd = iEnd;
	while (iStart < iEnd)
	{
		while (iPivot <= item[iEnd] && iStart < iEnd)
		{
			iEnd--;
		}
		if (iStart > iEnd)break;
		while (iPivot >= item[iStart] && iStart < iEnd)
		{
			iStart++;
		}
		if (iStart > iEnd)break;
		swap(&item[iStart], &item[iEnd]);
	}
	swap(&item[iBeginStart], &item[iStart]);

	if (iBeginStart < iStart)
		QuickSort(item, iBeginStart, iStart - 1);
	if (iBeginEnd > iEnd)
		QuickSort(item, iStart + 1, iBeginEnd);
}
void SetData(int item[], int iCount)
{
	srand((unsigned int)time(NULL));
	for (int a = 0; a < iCount; a++)
	{
		item[a] = rand() % iCount;
	}
	DataPrint(item, iCount);
}
void main()
{
	int item[10000];
	int count = 10000;

	clock_t sTime, eTime;

	cout << " How many numbers(MAX=10000?";
	scanf_s("%d", &count);
	getchar();

	printf("\nSelect Sort ");
	SetData(item, count);
	sTime = clock();
	SelectionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nBubble Sort ");
	SetData(item, count);
	sTime = clock();
	BubbleSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime => [%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nInsert Sort ");
	SetData(item, count);
	sTime = clock();
	InsertionSort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nshell Sort ");
	SetData(item, count);
	sTime = clock();
	shellsort(item, count);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nMerge Sort ");
	SetData(item, count);
	//item[0] = 6;
	//item[1] = 5;
	//item[2] = 3;
	//item[3] = 1;
	//item[4] = 8;
	//item[5] = 7;
	//item[6] = 2;
	//item[7] = 4;
	//count = 8;
	sTime = clock();
	MergeSort(item, 0, count - 1);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	printf("\nQuick Sort ");
	SetData(item, count);
	sTime = clock();
	QuickSort(item, 0, count - 1);
	eTime = clock() - sTime;
	printf("\n\ttime =>[%ld,%8.3f] => ", eTime, eTime / (double)CLK_TCK);
	DataPrint(item, count);

	getchar();
}