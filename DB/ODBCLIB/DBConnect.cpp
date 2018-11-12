#include "DBConnect.h"

BOOL DBConnect::Connect()
{
	// ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return FALSE;
	}
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return FALSE;
	}
	
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return FALSE;
	}
	

	// MDB ���Ͽ� �����ϱ�
	GetCurrentDirectory(MAX_PATH, m_cDir);

	
	m_rRet = SQLConnect(m_hDbc,
		(SQLTCHAR*)L"KHJUser", SQL_NTS,
		(SQLTCHAR*)L"sa", SQL_NTS,
		(SQLTCHAR*)L"kgca!@34", SQL_NTS);

	if ((m_rRet != SQL_SUCCESS) && (m_rRet != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;
		// �ܼ��� ����
		SQLError(m_hEnv, m_hDbc, m_hStmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);

		// ��� ���� ������
		int iErrorCnt = 1;
		while (m_rRet = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDbc, iErrorCnt++, sqlstate, &sqlcode,
			buffer, sizeof(buffer), &length) != SQL_NO_DATA)
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return FALSE;
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return 0;
	}
	return TRUE;
}
void DBConnect::DisConnect()
{
	// ������
	if (m_hStmt)SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	if (m_hDbc)SQLDisconnect(m_hDbc);
	if (m_hDbc)SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	if (m_hEnv)SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}

DBConnect::DBConnect()
{
}


DBConnect::~DBConnect()
{
}
