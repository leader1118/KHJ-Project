#pragma warning (disable : 4996)
#include <windows.h> // ODBC 위에 windows.h 
#include <stdlib.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>

//SQLServer의 프로시저를 사용해서 바꾸는 작업을 한 프로젝트

SQLHENV      g_hEnv; // 핸들
SQLHDBC      g_hDbc; // 핸들
SQLHSTMT   g_hStmt; // 핸들

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
		wsprintf(str, _T("SQLSTATE:%s, 진단정보:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("진단 정보"), 0);
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


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL 명령어를 실행
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
	// 명령핸들
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);

	SQLCHAR ID[20] = { 0, };
	SQLCHAR PS[20] = { 0, };

	SQLLEN LID, LPS;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, ID, sizeof(ID), &LID); // 리턴 받는걸 Name으로 받는다
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, PS, sizeof(PS), &LPS);
	// 작업구간      // 조회            // 시가라는 테이블로부터 이름으로 되어있는것 전부다 리턴 // "select name,price,korean from tblCigar" SQL 명령어
	//if (SQLExecDirect(g_Stmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar where name = 'this'"), SQL_NTS) != SQL_SUCCESS)

	SWORD sReturn;
	SQLINTEGER cbRetParam;
	SQLBindParameter(g_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);


	SQLBindParameter(g_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_INTEGER, 0, 0, &sReturn, 0, NULL);
	SQLRETURN ret=0;
	if (SQLExecDirect(g_hStmt,
		(SQLTCHAR*)_T("{?=CALL usp_Test(?)}"), SQL_NTS) // 저장프로시저 이름으로 불러올수 있드아
		!= SQL_SUCCESS)
	{
		HandleDiagnosticRecord(g_hStmt,SQL_HANDLE_STMT,ret);
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		printf("\nID : %s\tPS : %s", ID, PS);
	}

	// 커서를 해제시켜준다 (맨위로 올려준다)  // 이유 커서가 있는곳으로 부터 검색을 하기때문에 맨위로 올려준다고 생각하면된다.
	SQLCloseCursor(g_hStmt);
}

bool Delete()
{
	TCHAR      szSQL[256] = { 0, };
	wsprintf(szSQL, _T("Delete from UserList where userid='aaa'"));


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL 명령어를 실행
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


	if (SQLExecDirect(g_hStmt, szSQL, SQL_NTS) // SQL 명령어를 실행
		== SQL_SUCCESS)
	{
		SQLCloseCursor(g_hStmt);
		Select();
		return true;
	}
	SQLCloseCursor(g_hStmt);
	return false;
}


// 오픈 데이타 베이스
void main()
{
	// 분산을 잘해야한다.
	// 기본 포맷은 32비트
	// 환경-> 연결
	// 환경핸들은 부모가 NULL

	// 환경핸들
	if (SQLAllocHandle(
		SQL_HANDLE_ENV,
		SQL_NULL_HANDLE,
		&g_hEnv) != SQL_SUCCESS)      // 할당하고자하는 함수 
	{
		return;
	}

	if (SQLSetEnvAttr(
		g_hEnv,
		SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3,          // 버전
		SQL_IS_INTEGER) != SQL_SUCCESS)       // 할당 받았으니 값을 넣어준다 세팅해준다.
	{
		return;
	}



	// 연결핸들

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
		printf("\n0 : 출력 1: 추가 2: 삭제 3: 수정 \n");
		scanf_s("%d", &iSelect);
		switch (iSelect)
		{
		case 0: Select(); break;
		case 1: Add(); break;
		case 2: Delete(); break;
		case 3: Update(); break;
		}
	}


	// 삭제 반대순서로
	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc); // 연결을 끊어줘야한다.
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}