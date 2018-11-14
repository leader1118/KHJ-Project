#include "DB_CONNECT.h"


void DB_CONNECT::DBConnect()
{
	// 환경핸들
	if (SQLAllocHandle(
		SQL_HANDLE_ENV,
		SQL_NULL_HANDLE,
		&m_hENV) != SQL_SUCCESS) // 할당하고자 하는 함수
	{
		return;
	}

	if (SQLSetEnvAttr(
		m_hENV,
		SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3, // 버전
		SQL_IS_INTEGER)!=SQL_SUCCESS) // 할당 받았으니 값을 넣어준다, 세팅
	{
		return;
	}
	// 연결핸들
	SQLAllocHandle(SQL_HANDLE_DBC, m_hENV, &m_hDBC);
	
	SQLRETURN RET;
	TCHAR		m_InCon[255];
	SQLTCHAR	m_OutCon[255];
	SQLSMALLINT	m_cbOutCon;

	RET = SQLDriverConnect(m_hDBC, NULL, (SQLTCHAR*)m_InCon, _countof(m_InCon), m_OutCon, _countof(m_OutCon), &m_cbOutCon, SQL_DRIVER_NOPROMPT);

	RET= SQLConnect(
		m_hDBC,
		(SQLTCHAR*)L"KHJUser", SQL_NTS,
		(SQLTCHAR*)L"sa", SQL_NTS,
		(SQLTCHAR*)L"kgca!@34", SQL_NTS);
	if (RET != SQL_SUCCESS && RET != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC,&m_hSTMT);
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
