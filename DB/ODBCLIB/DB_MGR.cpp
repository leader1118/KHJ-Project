#include "DB_MGR.h"
SQLRETURN DB_MGR::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	int ret;
	SQLINTEGER	NativeError;
	SQLTCHAR	SqlState[6], Msg[255];
	SQLSMALLINT	MsgLen;
	TCHAR str[256];

	ret = 1;
	while (RetCode = SQLGetDiagRec(hType, hHandle, ret, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str, _T("SQLSTATE : %s, 진단정보 : %s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("진단 정보"), 0);
		ret++;
	}
	return RetCode;
}
bool	DB_MGR::ADDDATA()
{
	USERINFO	U_info;
	printf("추가할 아이디 :");
	scanf("%s", &U_info.UserID);
	printf("\n비밀 번호 :");
	scanf("%s", &U_info.UserPS);
	wsprintf(U_info.szSQL, _T("insert into KHJUser(UserId, UserPs) values('%s', '%s')"), L"qqaa", L"dddd");

	if (SQLExecDirect(m_hSTMT, U_info.szSQL, SQL_NTS) == SQL_SUCCESS) // SQL 명령어를 실행
	{
		SQLCloseCursor(m_hSTMT);
		SELECTDATA();
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;

}
void	DB_MGR::SELECTDATA()
{
	USERINFO	U_info;
	
	SQLLEN		UID, UPS;
	SQLBindCol(m_hSTMT, 1, SQL_C_CHAR, U_info.UserID, sizeof(U_info.UserID), &UID); 
	SQLBindCol(m_hSTMT, 2, SQL_C_CHAR, U_info.UserPS, sizeof(U_info.UserPS), &UPS);

	/*SWORD sRET;
	SQLINTEGER	cbRetparam;
	SQLBindParameter(m_hSTMT, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &sRET, 0, &cbRetparam);
	SQLBindParameter(m_hSTMT, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_INTEGER, 0, 0, &sRET, 0, NULL);*/
	
	SQLRETURN RET = 0;
	if (SQLExecDirect(
		m_hSTMT,
		(SQLTCHAR*)_T("{CALL dbo.usp_LogInTime}"), SQL_NTS) != SQL_SUCCESS)
	{
		HandleDiagnosticRecord(m_hSTMT, SQL_HANDLE_STMT, RET);
		return;
	}
	

	while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	{
		printf("\n USERID : %s \t USERPS : %s", U_info.UserID, U_info.UserPS);
	}

	SQLCloseCursor(m_hSTMT);
}
void	DB_MGR::SELECTOUTDATA()
{
	USERINFO	U_info;

	SQLLEN		UID, UPS;
	SQLBindCol(m_hSTMT, 1, SQL_C_CHAR, U_info.UserID, sizeof(U_info.UserID), &UID);
	SQLBindCol(m_hSTMT, 2, SQL_C_CHAR, U_info.UserPS, sizeof(U_info.UserPS), &UPS);

	/*SWORD sRET;
	SQLINTEGER	cbRetparam;
	SQLBindParameter(m_hSTMT, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &sRET, 0, &cbRetparam);
	SQLBindParameter(m_hSTMT, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_INTEGER, 0, 0, &sRET, 0, NULL);*/

	SQLRETURN RET = 0;
	
	if (SQLExecDirect(
		m_hSTMT,
		(SQLTCHAR*)_T("{?=CALL dbo.usp_LogoutTime(??)}"), SQL_NTS) != SQL_SUCCESS)
	{
		HandleDiagnosticRecord(m_hSTMT, SQL_HANDLE_STMT, RET);
		return;
	}

	while (SQLFetch(m_hSTMT) != SQL_NO_DATA)
	{
		printf("\n USERID : %s \t USERPS : %s", U_info.UserID, U_info.UserPS);
	}

	SQLCloseCursor(m_hSTMT);
}

bool	DB_MGR::DELETEDATA()
{
	USERINFO	U_info;
	printf("삭제할 아이디 :");
	scanf("%s", &U_info.UserID);
	wsprintf(U_info.szSQL, _T("Delete from KHJUser where UserId = '%s'"), U_info.UserID);

	if (SQLExecDirect(m_hSTMT, U_info.szSQL, SQL_NTS) == SQL_SUCCESS)
	{
		SQLCloseCursor(m_hSTMT);
		SELECTDATA();
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;
}
bool	DB_MGR::UPDATE()
{
	USERINFO	U_info;
	printf("기존 아이디:");
	scanf("%s", &U_info.UserID);
	printf("\n새로운 아이디:");
	scanf("%s", &U_info.NewUserID);
	wsprintf(U_info.szSQL, _T("Update KHJUser set UserId = '%s' where UserId \ '%s'"), U_info.UserID, U_info.NewUserID);

	if (SQLExecDirect(m_hSTMT, U_info.szSQL, SQL_NTS) == SQL_SUCCESS)
	{
		SQLCloseCursor(m_hSTMT);
		SELECTDATA();
		return true;
	}
	SQLCloseCursor(m_hSTMT);
	return false;
}
DB_MGR::DB_MGR()
{
}


DB_MGR::~DB_MGR()
{
}
