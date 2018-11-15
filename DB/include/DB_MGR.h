#pragma once
#include "DB_CONNECT.h"
struct USERINFO
{
	SQLTCHAR		szSQL[256] = { 0, };
	SQLTCHAR		UserID[20] = { 0, };
	SQLTCHAR		UserPS[20] = { 0, };
	SQLTCHAR		NewUserID[20] = { 0, };
	SQLTCHAR		OldUserID[20] = { 0, };
};
class DB_MGR: public DB_CONNECT
{
public:
	bool Add();
	bool Delete();
	bool Update();
	void Select();
public:
	DB_MGR();
	virtual ~DB_MGR();
};

