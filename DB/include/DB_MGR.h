#pragma once
#include "DB_CONNECT.h"
struct USERINFO
{
	SQLTCHAR		szSQL[256] = { 0, };
	SQLTCHAR		UserID[20] = { 0, };
	SQLTCHAR		UserPS[20] = { 0, };
	SQLTCHAR		NewUserID[20] = { 0, };
};
class DB_MGR: public DB_CONNECT
{
public:
	bool		ADDDATA();
	void		SELECTDATA();
	void		SELECTOUTDATA();
	bool		DELETEDATA();
	bool		UPDATE();
public:
	SQLRETURN HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);
public:
	DB_MGR();
	virtual ~DB_MGR();
};

