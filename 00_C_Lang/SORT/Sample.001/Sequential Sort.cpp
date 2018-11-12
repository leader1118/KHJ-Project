////순차 정렬(Sequential Sort)
///*순차 정렬은 맨 앞에서 부터 제일 작은 원소를 배치하게 만들어 나가는 알고리즘이다*/
//#include <stdio.h>
//#include<conio.h>
//
//#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환
//
//
//void SequenceSort(int *base, int n);
//int main(void)
//{
//	int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
//	SequenceSort(arr, 10);
//	_getch();
//	return 0;
//}
//void ViewArr(int *arr, int n);
//void SequenceSort(int *base, int n)
//{
//	int i, j;
//	ViewArr(base, n);//현재 상태 출력
//	for (i = 0; i<n; i++)
//	{
//		for (j = i; j<n; j++)
//		{
//			if (base[i]>base[j])//앞쪽 원소가 더 크면
//			{
//				SWAP(base[i], base[j]);//교환
//				ViewArr(base, n);//상태 출력
//			}
//		}
//	}
//}
//
//void ViewArr(int *arr, int n)
//{
//	int i = 0;
//	for (i = 0; i<n; i++)
//	{
//		printf("%2d ", arr[i]);
//	}
//	printf("\n");
//}
//
