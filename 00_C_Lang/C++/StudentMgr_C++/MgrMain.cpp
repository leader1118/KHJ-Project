#include "SStudent.h"
#include "LinkedList.h"


int main()
{
	cout << "========================================\n" << endl;
	cout << "============성적관리프로그램============\n" << endl;
	cout << "========================================\n " << endl;

	int MaxCount = 0;


	LinkedList FIND;
	while (1)
	{
		cout << "신규(1)" << "출력(2)"  << "번호검색(3)" <<
			 "저장(4)" << "불러오기(5)" <<"추가(6)"<<"삭제(7)"<< "종료(6)" << endl;
		scanf("%d", &MaxCount);

		if (MaxCount == EXIT)break;
		system("cls");
		switch (MaxCount)
		{
		case DataNew:
		{
			FIND.Insert();
		}break;
		case DataPrint:
		{
			FIND.printAll();
		}break;
		
		case IndexFind:
		{
			FIND.Find();
		}break;
		case SaveData:
		{
			FIND.save();
		}break;
		case LoadData:
		{
			FIND.Load();
		}break;
		case AddData:
		{

		}break;
		case DelData:
		{

		}break;
		
		}
	}
	_getch();
	return 0;

}