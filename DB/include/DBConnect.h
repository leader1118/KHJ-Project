#pragma once
#include "ODBCSTD.h"
class DBConnect
{
public:
	SQLHENV			m_hEnv;		 // 환경 핸들
	SQLHDBC			m_hDbc;	     // 연결 핸들
	SQLHSTMT		m_hStmt;	 // 명령 핸들
public:
	HWND			m_hList;
	HWND			m_hUserID;
	HWND			m_hUserPS;
	HWND			m_hCreateID;
	HWND			m_hDlgMain;
public:
	// 연결 설정을 위한 변수들
	TCHAR			m_cIncon[255];
	SQLTCHAR		m_ScOutCon[1024];
	SQLSMALLINT		m_cbOutCon;
	TCHAR			m_cDir[MAX_PATH];
	SQLRETURN		m_rRet;
public:
	BOOL		Connect();
	void		DisConnect();
public:
	DBConnect();
	virtual ~DBConnect();
};

