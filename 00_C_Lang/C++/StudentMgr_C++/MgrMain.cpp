#include "SStudent.h"
#include "LinkedList.h"


int main()
{
	cout << "========================================\n" << endl;
	cout << "============�����������α׷�============\n" << endl;
	cout << "========================================\n " << endl;

	int MaxCount = 0;


	LinkedList FIND;
	while (1)
	{
		cout << "�ű�(1)" << "���(2)"  << "��ȣ�˻�(3)" <<
			 "����(4)" << "�ҷ�����(5)" <<"�߰�(6)"<<"����(7)"<< "����(6)" << endl;
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