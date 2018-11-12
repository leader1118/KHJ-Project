#pragma once
#include "ODBCSTD.h"
class DBConnect
{
public:
	SQLHENV			m_hEnv;		 // ȯ�� �ڵ�
	SQLHDBC			m_hDbc;	     // ���� �ڵ�
	SQLHSTMT		m_hStmt;	 // ��� �ڵ�
public:
	HWND			m_hList;
	HWND			m_hUserID;
	HWND			m_hUserPS;
	HWND			m_hCreateID;
	HWND			m_hDlgMain;
public:
	// ���� ������ ���� ������
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

