#include "ODBCMGR.h"

void main()
{
	ODBCMGR odb;

	odb.Connect();

	while (1)
	{
		int Select = 0;
		printf("\n 1: 출력 2: 추가 3: 불러오기? 4: 수정 5:삭제");
		printf("\n 번호를 입력하시요 :");
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