//버블 정렬(Bubble Sort)
/*앞에서 부터 이웃하는 원소의 값을 비교하여 위치를 교환하는 것을 반복하며 끝까지
반복하면 제일 큰 값이 맨뒤에 위치한다.그리고 정렬할 개수를 1 줄인후 다시 반복하며
정렬할 원소의 개수가 1이면 모든 반복이 완료*/
#include <stdio.h>
#include<conio.h>

#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환


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
	ViewArr(base, n);//현재 상태 출력
	for (i = n; i>1; i--)//정렬할 범위를 축소해 나갑니다.
	{
		for (j = 1; j<i; j++)
		{
			if (base[j - 1]>base[j])//앞쪽 원소가 더 크면
			{
				SWAP(base[j - 1], base[j]);//교환
				ViewArr(base, n);//상태 출력
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

