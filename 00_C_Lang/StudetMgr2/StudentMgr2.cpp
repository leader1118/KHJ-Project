#include"StudentMgr2.h"

void main()
{
	srand(time(NULL));
	int select;
	while (1)
	{
		printf("\n 신규:0 출력:1 검색이름 :2 번호검색:3 저장:4 불러오기:5 추가:6 삭제:7 수정:8종료(99)");
		scanf_s("%d", &select);

		if (select == Exit)break;
		system("cls");
		switch(select)
		{
		case NewData:
		{
				DataNew();
		}break;
		case PrintData:
		{
			DataPrint();
		}break;
		case FindNameData:
		{
			DataFindName();
		}break;
		case FindIndexData:
		{
			DataFindIndex();
		}break;
		case SaveData:
		{
			DataSave();
		}break;
		case LoadData:
		{
			DataLoad();
		}break;
		case AddData:
		{
			DataAdd();
		}break;
		case DeleteData:
		{
			DataDelete();
		}break;
		case EditData:
		{
			DataEdit();
		}break;
		}
	}
	free(pStudentData);

	printf("\n 아무키나 누르면 종료됩니다");
	_getch();
	return 0;
}