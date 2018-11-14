#pragma once
#include "DB_CONNECT.h"
struct USERINFO
{
	TCHAR		szSQL[256] = { 0, };
	SQLCHAR*	UserID[20] = { 0, };
	SQLCHAR*	UserPS[20] = { 0, };
	SQLCHAR*	NewUserID[20] = { 0, };
};
class DB_MGR: public DB_CONNECT
{
public:
	bool		ADDDATA();
	void		SELECTDATA();
	bool		DELETEDATA();
	bool		UPDATE();
public:
	SQLRETURN HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);
public:
	DB_MGR();
	virtual ~DB_MGR();
};

