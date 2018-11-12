//쉘 정렬(Shell Sort)
/*쉘 정렬은 삽입 정렬 알고리즘을 이용하는 정렬 방식이다.
같은 간격에 있는 원소들을 삽입 정렬 원리로 정렬하는 것을 
반복간격의 초기값은 배열의 크기 /2 이며 간격이 1일떄까지
1/2로 줄이면서 반복한다*/
#include <stdio.h>
#include <conio.h>
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환


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

	for (step = size / 2; step>0; step /= 2)//step의 폭을 1/2로 줄여간다.
	{
		printf("step:%d\n", step);
		for (i = 0; i<step; i++) //step 간격에 있는 요소들을 삽입정렬
		{
			InsertionSort2(base + i, size - i, step);
		}
	}
}

void InsertionSort2(int *base, int size, int step)
{
	int i, j;
	for (i = step; i<size; i += step)//정렬 대상 원소는 step 간격으로 이동
	{

		for (j = i; j>0; j -= step)//step 간격으로 앞으로 이동
		{
			if (base[j - step]>base[j])//앞쪽이 더 클 때
			{
				SWAP(base[j - step], base[j]);//교환
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
