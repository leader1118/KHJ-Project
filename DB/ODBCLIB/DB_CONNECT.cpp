#include "DB_CONNECT.h"


int DB_CONNECT::DBConnect()
{
	SQLRETURN	sRet;
	// 환경 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hENV);
	if (sRet != SQL_SUCCESS)
	{
		return -1;
	}
	sRet = SQLSetEnvAttr(m_hENV, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (sRet != SQL_SUCCESS)
	{
		return -1;
	}
	// 연결 핸들
	sRet = SQLAllocHandle(SQL_HANDLE_DBC, m_hENV, &m_hDBC);
	SQLTCHAR szInCon[256];
	SQLSMALLINT cbOutCon;
	_stprintf_s(szInCon, 256, _T("%s"), _T("DRIVER ={SQL Server};Server = shader.kr;Address=192.168.0.28,1433;Network=dbmssocn;Database=KHJUser;Uid=sa;Pwd=kgca!@34;"));
	
	SQLTCHAR szOutCon[256] = { 0, };

	sRet = SQLDriverConnect(
		m_hDBC,
		NULL,
		(SQLTCHAR*)szInCon,
		_countof(szInCon),
		szOutCon,
		_countof(szOutCon),
		&cbOutCon,
		SQL_DRIVER_NOPROMPT);

	if ((sRet != SQL_SUCCESS) && (sRet != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;
		
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

		int m_ErrorCnt = 1;
		while (sRet = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDBC, m_ErrorCnt++, sqlstate, &sqlcode, buffer, sizeof(buffer), &length) != SQL_NO_DATA)
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return -1;
	}

	sRet = SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &m_hSTMT);
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
