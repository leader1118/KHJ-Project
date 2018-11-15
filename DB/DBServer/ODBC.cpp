#include "DB_MGR.h"

void main()
{
	DB_MGR	mgr;

	while (1)
	{
		int iSelect = 0;
		printf("\n 1: 출력 2: 추가 3: 수정 4:삭제");
		printf("\n 번호를 입력하시요 :");
		scanf("%d", &iSelect);
		mgr.DBConnect();

		switch (iSelect)
		{
		case 1: mgr.Select();
		{
			break;
		}
		case 2: mgr.Add();
		{
			break;
		}
		case 3: mgr.Update();
		{
			break;
		}
		case 4:	mgr.Delete();
		{
			break;
		}
		}
		//system("cls");
	}
	mgr.DBDisConnect();
}