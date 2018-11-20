#include "DB_MGR.h"
bool DB_MGR::Add()
{
	USERINFO info;
	char m_cName[20] = { 0, };
	char m_cPass[20] = { 0, };

	printf("아이디를 입력 하세요:");
	scanf("%s", &m_cName);
	MultiByteToWideChar(CP_ACP, 0, m_cName, -1, info.UserID, sizeof(m_cName));
	printf("\n비밀번호를 입력 하세요:");
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

	printf("삭제할 아이디를 입력하시요 :");
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

	printf("수정할 아이디를 입력하세요 :");
	scanf("%s", &OldName);
	MultiByteToWideChar(CP_ACP, 0, OldName, -1, info.OldUserID, sizeof(OldName));

	printf("새로운 아이디를 입력하세요 :");
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

	/*if (SQLExecDirect(m_hSTMT, (SQLTCHAR*)_T("select UserId,UserPs from KHJUser where name = '%s'"), SQL_NTS) != SQL_SUCCESS)
	{
		return;
	}*/

	SWORD sReturn=0;
	SQLINTEGER cbRetParam;
	SQLBindParameter(m_hSTMT, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);

	SQLBindParameter(m_hSTMT, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_INTEGER, 0, 0, &sReturn, 0, NULL);
	SQLRETURN ret = 0;
	if (SQLExecDirect(m_hSTMT,
		(SQLTCHAR*)_T("{?=CALL usp_Create1(?)}"), SQL_NTS) != SQL_SUCCESS)
	{
		//HandleDiagnosticRecord(m_hSTMT, SQL_HANDLE_STMT, ret);
		return;
	}

	while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	{
		printf("\nID : %s\tPS : %s", LID, LPS);
	}
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
		wsprintf(str, _T("SQLSTATE:%s, 진단정보:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("진단 정보"), 0);
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
