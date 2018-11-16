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

	wsprintf(info.szSQL, _T("Insert into KHJUser values('%s','%s')"), info.UserID, info.UserPS);
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
	SWORD sReturn;
	SQLLEN IBytes;
	IBytes = (SDWORD)12000;
	SQLINTEGER cbRetParam;
	SQLCHAR m_UserID[10];
	SQLINTEGER sLen = sizeof(m_UserID);
	SQLRETURN sRet;
	
	USERINFO info;

	SQLLEN UserName, UserPass;
	
	SQLBindCol(m_hSTMT, 1, SQL_C_CHAR, info.UserID, sizeof(info.UserID), &UserName);
	SQLBindCol(m_hSTMT, 2, SQL_C_CHAR, info.UserPS, sizeof(info.UserPS), &UserPass);

	printf(" 검색 아이디 :");
	scanf("%s", &m_UserID);
	SQLBindParameter(m_hSTMT, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &sReturn, sizeof(sReturn), &cbRetParam);
	SQLBindParameter(m_hSTMT, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, IBytes, 0, m_UserID, 0, NULL);
	sRet = SQLExecDirect(m_hSTMT, (SQLTCHAR*)_T("{?=CALL ??(??)}"), SQL_NTS);

	if (sRet != SQL_SUCCESS && sRet != SQL_SUCCESS_WITH_INFO)
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;

		SQLError(m_hENV, m_hDBC, m_hSTMT, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

		int iErrorCnt = 1;
		while (sRet = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDBC, iErrorCnt++, sqlstate, &sqlcode,
			buffer, sizeof(buffer),&length)!=SQL_NO_DATA);
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return;
	}
	system("cls");
	while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	{
		printf("UserID : %s \n UserPS : %s", (char*)info.UserID, (char*)info.OldUserID);
	}
	SQLCloseCursor(m_hSTMT);
}
DB_MGR::DB_MGR()
{
}


DB_MGR::~DB_MGR()
{
}
