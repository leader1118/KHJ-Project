#include "DB_MGR.h"

void main()
{
	USERINFO U_info;
	DB_MGR	mgr;

	mgr.DBConnect();

	while (1)
	{
		int Select = 0;
		printf("\n 1: ��� 2: �߰� 3: ���� 4:����");
		printf("\n ��ȣ�� �Է��Ͻÿ� :");
		scanf("%d", &Select);
		

		switch (Select)
		{
		case 1: mgr.SELECTDATA();
		{
			break; 
		}
		case 2: mgr.ADDDATA();
		{
			break;
		}
		case 3: mgr.UPDATE();
		{
			break;
		}
		case 4:	mgr.DELETEDATA();
		{
			break;
		}
		}
		system("cls");
	}
	mgr.DBDisConnect();
}