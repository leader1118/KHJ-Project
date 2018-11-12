//힙 정렬(Heap Sort)
/*힙 정렬은 힙 트리를 이용하는 알고리즘이다.
최대 힙을 사용하면 크기 순으로 정렬하고 최소 합을 사용하면 크기 역순으로 정렬한다.
힙 정렬은 먼저 힙트리를 구성하고 루트의 값과 맨 마지막 값을 교환한 후에 정렬 범위를 1 줄인다
반복하여 정렬 범위가 1일 때까지 반복한다.최대 힙 트리에서 루트는 최대 값을 갖는다
마지막 값과 교환 하면 제일 큰값이 맨 뒤로 배치할수 있다.
그 뒤에 정렬 범위를 줄여 나가면 최종적으로 정렬 상태가 완성*/
#include <stdio.h>
#include<conio.h>
#define LEFT_CHILD(x)    (2*x + 1)
#define RIGHT_CHILD(x) (2*x + 2)
#define PARENT(x)        ((x-1)/2)
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환


void HeapSort(int *base, int n);
void ViewArr(int *arr, int n);
int main(void)
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
	ViewArr(arr, 10);
	HeapSort(arr, 10);
	ViewArr(arr, 10);
	_getch();
	return 0;
}

void InitHeap(int *base, int n);
void MakeHeap(int *base, int n);
void HeapSort(int *base, int n)
{
	int on = n;
	printf("초기 힙 생성 과정\n");
	InitHeap(base, n);
	n--;
	SWAP(base[0], base[n]);
	printf("정렬 과정\n");
	while (n>1)
	{

		MakeHeap(base, n);
		ViewArr(base, n + 1);
		n--;
		SWAP(base[0], base[n]);
	}
	ViewArr(base, n + 1);
}

void InitHeap(int *base, int n)
{
	int pa = 0;
	int now;
	int i;
	for (i = 1; i<n; i++)//순차적으로 힙에 구성
	{
		now = i;
		while (now>0)//now의 인덱스가 0이 아니면(힙의 루트가 아니면)
		{
			pa = PARENT(now);//부모 인덱스 구함
			if (base[now]>base[pa])//부모보다 더 크면
			{
				SWAP(base[now], base[pa]);//부모와 교환
				now = pa;//인덱스를 부모로 설정
			}
			else//아니면 자리를 찾은 것임
			{
				break;
			}
		}
		ViewArr(base, i + 1);
	}
}


int FindMaxIndex(int *base, int n, int now);
void MakeHeap(int *base, int n)
{
	int now = 0;
	int mp = 0;
	//루트에 있는 요소를 힙 트리에 맞게 자리를 찾는 과정
	while (LEFT_CHILD(now) < n)//왼쪽 자식이 있다면
	{
		int mp = FindMaxIndex(base, n, now);//now와 왼쪽, 오른쪽 자식 중에 큰 값의 위치 찾음
		if (mp == now)//mp와 now가 같으면
		{
			break;//자리를 찾은 것임
		}
		SWAP(base[mp], base[now]);//now와 큰 값의 자리 교환
		now = mp;//큰 값의 위치를 now로 설정
	}
}


int FindMaxIndex(int *base, int n, int now)
{
	int lc = LEFT_CHILD(now);//왼쪽 자식
	int rc = RIGHT_CHILD(now);//오른쪽 자식

	if (rc >= n)//오른쪽 자식이 없을 때
	{
		if (base[now]<base[lc])
		{
			return lc;
		}
		return now;
	}
	if (base[lc]<base[rc])
	{
		return rc;
	}
	return lc;
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
