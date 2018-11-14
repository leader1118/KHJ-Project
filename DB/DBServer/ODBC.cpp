#include "DB_MGR.h"

void main()
{
	USERINFO U_info;
	DB_MGR	mgr;

	mgr.DBConnect();

	while (1)
	{
		int Select = 0;
		printf("\n 1: 출력 2: 추가 3: 수정 4:삭제");
		printf("\n 번호를 입력하시요 :");
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