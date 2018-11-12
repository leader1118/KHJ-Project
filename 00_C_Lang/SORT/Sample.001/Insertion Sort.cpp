//삽입 정렬(Insertion Sort)
/*삽입 정렬 알고리즘은 점진적으로 정렬 범위를 넓혀 나가는 방식으로 정렬하는 알고리즘이다.
이를 위해 새로운 범위에 포함하는 마지막 원소를 앞으로 이동하면서 자신보다 작은
요소를 찾을 떄까지 이동하면서 자리를 교환한다*/
#include <stdio.h>
#include<conio.h>

#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환

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

	ViewArr(base, n);//현재 상태 출력
	for (i = 1; i < n; i++)//정렬할 범위를 확대해 나갑니다.
	{
		for (j = i; j > 0; j--)
		{
			if (base[j - 1] > base[j])//앞쪽 원소가 더 크면
			{
				SWAP(base[j - 1], base[j]);//교환
				ViewArr(base, n);//상태 출력
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
