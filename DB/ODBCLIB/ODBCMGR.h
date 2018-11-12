#pragma once
#include "DBConnect.h"
struct DBINFO // ��� ���� ���� �ޱ� ���� ������
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

