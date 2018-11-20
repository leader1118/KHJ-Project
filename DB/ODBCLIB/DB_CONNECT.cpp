#include "DB_CONNECT.h"


bool DB_CONNECT::DBConnect()
{
	TCHAR	InCon[255];
	SQLTCHAR OutCon[1024];
	SQLSMALLINT	cbOutCon;
	TCHAR Dir[MAX_PATH];
	SQLRETURN Ret;

	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hENV) != SQL_SUCCESS)
	{
		return FALSE;
	}
	if (SQLSetEnvAttr(m_hENV, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return FALSE;
	}

	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hENV, &m_hDBC) != SQL_SUCCESS)
	{
		return FALSE;
	}

	GetCurrentDirectory(MAX_PATH, Dir);

	_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=192.168.0.28,1433;Network=dbmssocn;Database=KHJUser;Uid=sa;Pwd=kgca!@34;"));
	Ret = SQLDriverConnect(m_hDBC, NULL, (SQLTCHAR*)InCon, _countof(InCon), OutCon, _countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;

		SQLError(m_hENV, m_hDBC, m_hSTMT, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

		int iErrorCnt = 1;
		while (Ret = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDBC, iErrorCnt++, sqlstate, &sqlcode,
			buffer, sizeof(buffer), &length) != SQL_NO_DATA)
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return FALSE;
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &m_hSTMT) != SQL_SUCCESS)
	{
		return 0;
	}
	return TRUE;
}
void DB_CONNECT::DBDisConnect()
{
	// 삭제는 반대순서로 해야한다.
	SQLFreeHandle(SQL_HANDLE_STMT, m_hSTMT);
	SQLDisconnect(m_hDBC);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDBC);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hENV);
}

DB_CONNECT::DB_CONNECT()
{
}


DB_CONNECT::~DB_CONNECT()
{
}
