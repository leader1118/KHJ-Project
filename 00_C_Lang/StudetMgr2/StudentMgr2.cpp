#include"StudentMgr2.h"

void main()
{
	srand(time(NULL));
	int select;
	while (1)
	{
		printf("\n �ű�:0 ���:1 �˻��̸� :2 ��ȣ�˻�:3 ����:4 �ҷ�����:5 �߰�:6 ����:7 ����:8����(99)");
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

	printf("\n �ƹ�Ű�� ������ ����˴ϴ�");
	_getch();
	return 0;
}