#include "DB_MGR.h"

void main()
{
	DB_MGR	mgr;

	while (1)
	{
		int iSelect = 0;
		printf("\n 1: ��� 2: �߰� 3: ���� 4: ���� 5: �˻�");
		printf("\n ��ȣ�� �Է��Ͻÿ� :");
		scanf("%d", &iSelect);
		mgr.DBConnect();

		switch (iSelect)
		{
		case 1: mgr.Select();
		{
			system("pause");
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
		case 5: mgr.FindSelect();
		{
			system("pause");
			break;
		}
		}
		system("cls");
	}
	mgr.DBDisConnect();
}