#include "ODBCMGR.h"

void main()
{
	ODBCMGR odb;

	odb.Connect();

	while (1)
	{
		int Select = 0;
		printf("\n 1: ��� 2: �߰� 3: �ҷ�����? 4: ���� 5:����");
		printf("\n ��ȣ�� �Է��Ͻÿ� :");
		scanf("%d", &Select);

		switch (Select)
		{
		case 1: odb.ReadRecord(); 
		{
			break; 
		}
		case 2: odb.AddRecord(); 
		{
			break;
		}
		case 3: odb.DBExecuteSQL(); 
		{
			break;
		}
		case 4:	odb.UpdateRecord(); 
		{
			break;
		}
		case 5: odb.DeleteRecord(); 
		{
			break;
		}
		}
	}
	odb.DisConnect();
}