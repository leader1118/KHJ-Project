#pragma once
#include "DBConnect.h"
struct DBINFO // 결과 값을 돌려 받기 위한 변수들
{
	SQLCHAR Name[21];
	int		PS;
	bool	CreateID;
	SQLLEN	INFO_UserID;
	SQLLEN	INFO_UserPS;
	SQLLEN	INFO_CreateID;
};
class ODBCMGR : public DBConnect
{
public:
	BOOL DBExecuteSQL();
	BOOL ReadRecord();
public:
	void AddRecord();
	void DeleteRecord();
	void UpdateRecord();
	
public:
	ODBCMGR();
	virtual ~ODBCMGR();
};

