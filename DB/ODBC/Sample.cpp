#pragma warning (disable : 4996)
#include <windows.h> // ODBC ���� windows.h 
#include <stdlib.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>

//SQLServer�� ���ν����� ����ؼ� �ٲٴ� �۾��� �� ������Ʈ

SQLHENV      g_hEnv; // �ڵ�
SQLHDBC      g_hDbc; // �ڵ�
SQLHSTMT   g_hStmt; // �ڵ�

bool Add();
void Select();
bool Delete();
bool Update();

SQLRETURN HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
	int ii;
	SQLINTEGER NativeError;
	SQLTCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	TCHAR str[256];

	ii = 1;
	while (RetCode = SQLGetDiagRec(hType, hHandle, ii, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str, _T("SQLSTATE:%s, ��������:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("���� ����"), 0);
		ii++;
	}
	return RetCode;
}


//Insert into tblcigar (name,prive,korean)values('aaa',3000,1)
//_T("Insert into tblcigar (name,price,korean)values('bbb',3000,1)");



bool Add()
{
	TCHAR      szSQL[256] = { 0, };
	SQLTCHAR   ID[20] = L"aaa";
	SQLTCHAR   PS[20] = L"WWW";
	wsprintf(szSQL, _T("Insert into UserList (userid, userpass)values('%s','%s')"), ID, PS);


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL ��ɾ ����
		== SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		Select();
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}


// select ,, from table
// select ,, from table where ?=?


void Select()
{
	// ����ڵ�
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);

	SQLCHAR ID[20] = { 0, };
	SQLCHAR PS[20] = { 0, };

	SQLLEN LID, LPS;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), &LID); // ���� �޴°� Name���� �޴´�
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, PS, sizeof(PS), &LPS);
	// �۾�����      // ��ȸ            // �ð���� ���̺�κ��� �̸����� �Ǿ��ִ°� ���δ� ���� // "select name,price,korean from tblCigar" SQL ��ɾ�
	//if (SQLExecDirect(g_Stmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar where name = 'this'"), SQL_NTS) != SQL_SUCCESS)

	SWORD sReturn;
	SQLINTEGER cbRetParam;
	SQLBindParameter(g_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);


	SQLBindParameter(g_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_INTEGER, 0, 0, &sReturn, 0, NULL);
	SQLRETURN ret=0;
	if (SQLExecDirect(g_hStmt,
		(SQLTCHAR*)_T("{?=CALL usp_Test(?)}"), SQL_NTS) // �������ν��� �̸����� �ҷ��ü� �ֵ��
		!= SQL_SUCCESS)
	{
		HandleDiagnosticRecord(g_hStmt,SQL_HANDLE_STMT,ret);
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		printf("\nID : %s\tPS : %s", ID, PS);
	}

	// Ŀ���� ���������ش� (������ �÷��ش�)  // ���� Ŀ���� �ִ°����� ���� �˻��� �ϱ⶧���� ������ �÷��شٰ� �����ϸ�ȴ�.
	SQLCloseCursor(g_hStmt);
}

bool Delete()
{
	TCHAR      szSQL[256] = { 0, };
	wsprintf(szSQL, _T("Delete from UserList where userid='aaa'"));


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL ��ɾ ����
		== SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		Select();
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}

bool Update()
{
	TCHAR      szSQL[256] = { 0, };
	wsprintf(szSQL, _T("Update UserList set userid='ccc' where userid='aaa'"));


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL ��ɾ ����
		== SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		Select();
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}


// ���� ����Ÿ ���̽�
void main()
{
	// �л��� ���ؾ��Ѵ�.
	// �⺻ ������ 32��Ʈ
	// ȯ��-> ����
	// ȯ���ڵ��� �θ� NULL

	// ȯ���ڵ�
	if (SQLAllocHandle(
		SQL_HANDLE_ENV,
		SQL_NULL_HANDLE,
		&g_hEnv) != SQL_SUCCESS)      // �Ҵ��ϰ����ϴ� �Լ� 
	{
		return;
	}

	if (SQLSetEnvAttr(
		g_hEnv,
		SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3,          // ����
		SQL_IS_INTEGER) != SQL_SUCCESS)       // �Ҵ� �޾����� ���� �־��ش� �������ش�.
	{
		return;
	}



	// �����ڵ�

	SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc);

	SQLRETURN ret = SQLConnect(g_hDbc,
		(SQLTCHAR*)L"112.216.123.139", SQL_NTS,
		(SQLTCHAR*)L"sa", SQL_NTS,
		(SQLTCHAR*)L"kgca!@34", SQL_NTS);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}


	while (1)
	{
		int iSelect;
		printf("\n0 : ��� 1: �߰� 2: ���� 3: ���� \n");
		scanf_s("%d", &iSelect);
		switch (iSelect)
		{
		case 0: Select(); break;
		case 1: Add(); break;
		case 2: Delete(); break;
		case 3: Update(); break;
		}
	}


	// ���� �ݴ������
	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc); // ������ ��������Ѵ�.
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}