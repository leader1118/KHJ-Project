#include <iostream>
#include <time.h>

void DataPrint(int list[], int iNum)
{
	//return;
	for (int i = 0; i < iNum; i++)
	{
		std::cout << list[i] << " ";
	}
	std::cout << std::endl<<std::endl;
}
void SetData(int list[], int iNum)
{
	srand(time(NULL));
	for (int i = 0; i < iNum; i++)
	{
		list[i] = rand() % 100;
	}
	DataPrint(list, iNum);
}
bool swap(int& a, int& b)
{

	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
		return true;
	}
	return false;
}
void change(int& a, int& b)
{

	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}	
}
void SelectionSort(int list[], int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		for (int j = i + 1; j < iNum; j++)
		{
			swap(list[i], list[j]);
		}
	}
}
void insertionSort(int list[], int iNum, int s = 1, int step = 1)
{
	for (int i = s; i < iNum; i += step)
	{
		int temp = list[i];
		int j = i - step;
		for (; j >= 0; j -= step)
		{
			int temp = list[i];
			if (list[j] > temp)
			{
				list[j + step] = list[j];
				continue;
			}
			swap(list[i], list[j]);
			break;
		}
		list[j + step] = temp;
	}
}
void bubbleSort(int list[], int iNum)
{
	for (int i = 0; i < iNum - 1; i++)
	{
		bool bflag = false;
		for (int j = i + 1; j < iNum - i - 1; j++)
		{
			if(bflag = swap(list[j], list[i + 1]));
			{
				bflag = true;
			}
		}
		if (bflag == false)
		{
			break;
		}
	}
}
void ShellSort(int list[], int iNum)
{
	//n=3*x+1;
	//x=(n-1) / 3;
	//1,4,13,40,121,364,1093...........;
	int g;
	for (g = 1; g < iNum; g = 3 * g + 1);
	for (g /= 3; g > 0; g /= 3);

	int k = g; // 그룹의 개수
	while (k > 1)
	{
		k = k / 2;
		for (int s = 0; s < k; s++)
		{                           //시작,간격
			insertionSort(list, iNum, s, k);
		}
	}
}
void QuickSort(int list[], int iStart, int iEnd)
{
	int iPivot = list[iStart];
	int iBeginStart = iStart;
	int iBeginEnd = iEnd;
	while (iStart < iEnd)
	{
		while (iPivot <= list[iEnd] && iStart < iEnd)
		{
			iEnd--;
		}
		while (iPivot >= list[iStart] && iStart < iEnd)
		{
			iStart++;
		}
		if (iStart > iEnd) break; 
		swap(list[iStart], list[iEnd]);
	}
	swap(list[iBeginStart], list[iStart]);

	if (iBeginStart < iStart)
	QuickSort(list, iBeginStart, iStart-1);
	if (iBeginEnd > iEnd)
	QuickSort(list,iStart+1,iBeginEnd);

}
void BuildHeap(int list[], int n)
{
	for(int i = 1; i < n; i++)
	{
		int iChild = i;
		do {
			int iRoot = (iChild = -1) / 2;
			if (list[iRoot] < list[iChild])
			{
				change(list[iRoot], list[iChild]);
			}
			iChild = iRoot;
		} while (iChild != 0);
	}
}
void RebuildHeap(int list[], int n)
{
	
	for (int iLast = n-1; iLast >= 0; iLast--)
	{
		change(list[0], list[iLast]);
		int iRoot = 0;
		int iChild;
		do {
			iChild = 2 * iRoot + 1;

			int iRoot = (iChild = -1) / 2;
			if (iChild<iLast-1 && list[iChild] < list[iChild+1])
			{
				iChild++;
			}
			if (iChild<iLast &&list[iRoot] < list[iChild])
			{
				change(list[iRoot], list[iChild]); 
			}
			iRoot = iChild;
		} while (iChild != iLast);
	}
}
void HeapSort(int list[], int n)
{
	BuildHeap(list, n);
	RebuildHeap(list, n);
}
const int g_iMaxCnt = 10;
void main()
{
	int item[g_iMaxCnt];//_countof
	int* pitem = new int[20];
	SetData(item, _countof(item));
	clock_t sTime, eTime;
	
	sTime = clock(); //1000: 1초
	SelectionSort(item, g_iMaxCnt);
	eTime = clock() - sTime;
	std::cout << "SelectionSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	SetData(item, _countof(item));
	sTime = clock(); //1000: 1초
	bubbleSort(item, g_iMaxCnt);
	eTime = clock() - sTime;
	std::cout << "bubbleSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	SetData(item, _countof(item));
	sTime = clock(); //1000: 1초
	insertionSort(item, g_iMaxCnt);
	eTime = clock() - sTime;
	std::cout << "insertionSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	SetData(item, _countof(item));
	sTime = clock(); //1000: 1초
	ShellSort(item, g_iMaxCnt);
	eTime = clock() - sTime;
	std::cout << "ShellSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	SetData(item, _countof(item));
	sTime = clock(); //1000: 1초
	QuickSort(item, 0,g_iMaxCnt-1);
	eTime = clock() - sTime;
	std::cout << "QuickSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	SetData(item, _countof(item));
	sTime = clock(); //1000: 1초
	HeapSort(item, g_iMaxCnt);
	eTime = clock() - sTime;
	std::cout << "HeapSort-->" << eTime / (double)CLK_TCK << std::endl;
	DataPrint(item, g_iMaxCnt);

	system("pause");
}