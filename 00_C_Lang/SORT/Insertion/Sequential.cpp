#include<stdio.h>//printf문과 scanf문 사용하기 위한 헤더
#include<conio.h>//_getch()문 사용을 위한 헤더
#define SWAP(a,b) {int t; t=a; a=b; b=t;}//a와b를 교환

void SequenoeSort(int *base, int n); 
int main(void)//메인
{
	int arr[10] = { 9,4,3,10,5,8,7,6,2,1, }; // 배열 임의 초기화
	SequenoeSort(arr, 10);//함수 호출

	_getch();
	return 0;
}
void ViewArr(int *arr, int n); 
void SequenoeSort(int *base, int n)
{
	int i;
	int j;
	ViewArr(base, n); //현재 상태 출력

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (base[i] > base[j])//앞쪽 원소가 더 크면
			{
				SWAP(base[i], base[j]);//교환
				ViewArr(base, n);//상태 출력
			}
		}
	}

}
void ViewArr(int *arr, int n)// 현재 상태 배열 출력
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%2d\t", arr[i]);
	}
	printf("\n");
}