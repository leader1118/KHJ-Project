#include "Mgr.h"

void main()
{
	srand(time(NULL));
	int select;
	while (1)
	{
		printf("\n 신규 : 0 출력 :1 이름검색 :2 번호검색 :3 추가 :4 삭제 :5 저장 :6 불러오기 :7 EXIT : (99)");
		scanf("%d", &select);

		if (select == EXIT)break;//만약 EXIT선택시 종료
		system("cls");//선택시 삭제
		switch (select)
		{
		case NewData:
		{

		}break;
		case PrintData:
		{

		}break;
		case FindName:
		{

		}break;
		case FindIndex:
		{

		}break;
		case AddData:
		{

		}break;
		case DeleteData:
		{

		}break;
		case SaveData:
		{

		}break;
		case LoadData:
		{

		}break;
		}
	}
	free(pStudentFile);
	_getch();
	return;

}