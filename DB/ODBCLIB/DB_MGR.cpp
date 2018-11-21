#include "DB_MGR.h"
bool DB_MGR::Add()
{
	USERINFO info;
	char m_cName[20] = { 0, };
	char m_cPass[20] = { 0, };

	printf("���̵� �Է� �ϼ���:");
	scanf("%s", &m_cName);
	MultiByteToWideChar(CP_ACP, 0, m_cName, -1, info.UserID, sizeof(m_cName));
	printf("\n��й�ȣ�� �Է� �ϼ���:");
	scanf("%s", &m_cPass);
	MultiByteToWideChar(CP_ACP, 0, m_cPass, -1, info.UserPS, sizeof(m_cPass));

	wsprintf(info.szSQL, _T("Insert into KHJUser(UserId,UserPs) values('%s','%s')"), info.UserID, info.UserPS);
	SQLRETURN sRet;
	sRet = SQLExecDirect(m_hSTMT, info.szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(m_hSTMT);
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;
}
bool DB_MGR::Delete()
{
	USERINFO	info;
	char		m_cName[20] = { 0, };

	printf("������ ���̵� �Է��Ͻÿ� :");
	scanf("%s", &m_cName);
	MultiByteToWideChar(CP_ACP, 0, m_cName, -1, info.UserID, sizeof(m_cName));

	wsprintf(info.szSQL, _T("delete from KHJUser where UserId='%s'"), info.UserID);
	SQLRETURN sRet;
	sRet = SQLExecDirect(m_hSTMT, info.szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(m_hSTMT);
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;
}
bool DB_MGR::Update()
{
	USERINFO info;
	char OldName[20] = { 0, };
	char NewName[20] = { 0, };

	printf("������ ���̵� �Է��ϼ��� :");
	scanf("%s", &OldName);
	MultiByteToWideChar(CP_ACP, 0, OldName, -1, info.OldUserID, sizeof(OldName));

	printf("���ο� ���̵� �Է��ϼ��� :");
	scanf("%s", &NewName);
	MultiByteToWideChar(CP_ACP, 0, NewName, -1, info.NewUserID, sizeof(NewName));

	wsprintf(info.szSQL, _T("update KHJUser set UserId='%s' where UserId='%s'"), info.NewUserID, info.OldUserID);
	SQLRETURN sRet;
	sRet = SQLExecDirect(m_hSTMT, info.szSQL, SQL_NTS);
	if (sRet == SQL_SUCCESS)
	{
		SQLCloseCursor(m_hSTMT);
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;
}
void DB_MGR::Select()
{
	USERINFO info;
	SQLLEN LID, LPS;
	SQLBindCol(m_hSTMT, 1, SQL_C_CHAR, info.UserID, sizeof(info.UserID), &LID);
	SQLBindCol(m_hSTMT, 2, SQL_C_CHAR, info.UserPS, sizeof(info.UserPS), &LPS);

	SQLRETURN ret;

	ret = SQLExecDirect(m_hSTMT, (SQLTCHAR*)_T("select UserId, UserPs from KHJUser"), SQL_NTS);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
	}

	while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	{
		printf("\nID : %s\tPS : %s", info.UserID, info.UserPS);
	}


	//SWORD sReturn;
	//SQLLEN IBytes; 
	//SQLLEN LID, LPS;
	//IBytes = (SDWORD)12000;
	//SQLINTEGER cbRetParam;
	//SQLCHAR m_cUserID[10];
	//SQLINTEGER sLen = sizeof(m_cUserID);
	//SQLRETURN sRet;

	//SQLBindCol(m_hSTMT, 1, SQL_C_CHAR, info.UserID, sizeof(info.UserID), &LID);
	//SQLBindCol(m_hSTMT, 2, SQL_C_CHAR, info.UserPS, sizeof(info.UserPS), &LPS);

	//SQLBindParameter(m_hSTMT, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &sReturn, sizeof(sReturn), &cbRetParam);
	//SQLBindParameter(m_hSTMT, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, IBytes, 0, info.UserID, 0, NULL);
	//sRet = SQLExecDirect(m_hSTMT, (SQLTCHAR*)_T("{?= CALL ���ν���(?)}"), SQL_NTS);
	//

	//if (sRet != SQL_SUCCESS && sRet != SQL_SUCCESS_WITH_INFO)
	//{
	//	SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
	//	SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
	//	SQLINTEGER sqlcode;
	//	SQLSMALLINT length;
	//	// �ܼ��� ����
	//	SQLError(m_hENV, m_hDBC, m_hSTMT, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
	//	MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

	//	// ��� ���� ������.
	//	int iErrorCnt = 1;
	//	while (sRet = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDBC, iErrorCnt++, sqlstate, &sqlcode,
	//		buffer, sizeof(buffer), &length) != SQL_NO_DATA)
	//	{
	//		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
	//	}
	//	return;
	//}
	//system("cls");
	//while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	//{
	//	printf("\nID : %s\tPS : %s", LID, LPS);
	//}
	SQLCloseCursor(m_hSTMT);
}
SQLRETURN HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	int ii;
	SQLINTEGER NativeError;
	SQLTCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	TCHAR str[256];

	ii = 1;
	while (RetCode = SQLGetDiagRec(hType, hHandle, ii, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str, _T("SQLSTATE:%s, ��������:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("���� ����"), 0);
		ii++;
	}
	return RetCode;
}
DB_MGR::DB_MGR()
{
}


DB_MGR::~DB_MGR()
{
}
