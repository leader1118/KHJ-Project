#include "Mgr.h"

void main()
{
	srand(time(NULL));
	int select;
	while (1)
	{
		printf("\n �ű� : 0 ��� :1 �̸��˻� :2 ��ȣ�˻� :3 �߰� :4 ���� :5 ���� :6 �ҷ����� :7 EXIT : (99)");
		scanf("%d", &select);

		if (select == EXIT)break;//���� EXIT���ý� ����
		system("cls");//���ý� ����
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