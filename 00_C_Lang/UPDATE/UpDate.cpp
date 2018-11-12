#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
//#include <stdio.h>
#include <iostream>


#define IDD_DIALOGMAIN						101
#define IDC_LISTUSER						1001
#define IDC_BTNADD							1002
#define IDC_BTNDEL						    1003
#define IDC_BTNUPDATE						1004
#define IDC_FUserID							1006
#define IDC_FUserPS							1007
#define IDC_FCreateTime                     1010

// 핸들
SQLHENV m_hEnv;   // 환경핸들
SQLHDBC m_hDbc;   // 연결핸들
SQLHSTMT m_hStmt; // 명령핸들

LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL DBConnect();
void DBDisConnect();
BOOL DBExecuteSQL();
HINSTANCE g_hInst;
HWND hDlgMain;
HWND hList, hUserID, hUserPS, hCreateTime;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdSHow)
{
	g_hInst = hInstance;

	if (DBConnect() == FALSE)
	{
		MessageBox(NULL, _T("데이터 베이스에 연결할 수 없습니다"), _T("에러"), MB_OK);
		return 0;
	}

	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOGMAIN), HWND_DESKTOP, (DLGPROC)MainDlgProc);

	DBDisConnect();
	return 0;
}

// 에러 발생시 진단 정보를 출력해 준다.
void PrintDiag()
{
	int ii;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLTCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	TCHAR str[256];

	ii = 1;
	while (Ret = SQLGetDiagRec(SQL_HANDLE_STMT, m_hStmt, ii, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str, _T("SQLSTATE: %s, 진단정보:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("진단 정보"), 0);
		ii++;
	}
}
BOOL DBConnect()
{
	// 연결 설정을 위한 변수들
	TCHAR InCon[255];
	SQLTCHAR OutCon[1024];
	SQLSMALLINT cbOutCon;
	TCHAR Dir[MAX_PATH];
	SQLRETURN Ret;

	// 환경 핸들을 할당하고 버전 속성을 설정한다.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) // 핸들을 할당한다
	{
		return FALSE;
	}
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) // 핸들의 버전속성을 정한다
	{
		return FALSE;
	}
	// 연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return FALSE;
	}
	// MDB 파일에 연결하기
	GetCurrentDirectory(MAX_PATH, Dir);
	// 주의 --> *.mdb,"한칸뛰어야 한다." *.accdb
	// <*accdb> 파일
	// _stprintf(InCon,_T("DRIVER={Microsoft Access Driver(*.mdb, *.accdb)}; DBQ=%s\\cigarette.accdb;"),Dir);
	//// <*.mdb> 파일
	// _stprintf(InCon, _T(DRIVER={Microsoft Access Driver(*.mdb, *.accdb)}; DBQ=%s\\cigarette.mdb;"),Dir);
	//// <*.dsn> 파일
	// _stprintf((TCHAR*))InCon, _T("FileDsn=%s"),_T("cigaretteaccdb.dsn"));
	// _stprintf((THCAR*)InCon,_T("Dsn=%s"),_T("SVRKGCA"));
	
	// SQLSERVER(client) 접속
	_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=112.216.123.139,1433;Network=dbmssocn;Database=KHJDB;Uid=sa;Pwd=kgca!@34;"));
	Ret = SQLDriverConnect(m_hDbc, NULL, (SQLTCHAR*)InCon, _countof(InCon), OutCon,
		_countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);
	
	Ret = SQLConnect(m_hDbc,
		(SQLTCHAR*)L"KHJUser", SQL_NTS,		// 테이블 이름
		(SQLTCHAR*)L"sa", SQL_NTS,			
		(SQLTCHAR*)L"kgca!@34", SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;
		// 단순한 에러
		SQLError(m_hEnv, m_hDbc, m_hStmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);  // MB_OK = ok 버튼 하나만 나타낸다

		// 모든 에러 나열됨
		int iErrorCnt = 1;
		while (Ret = SQLGetDiagRec(SQL_HANDLE_DBC, m_hDbc, iErrorCnt++, sqlstate, &sqlcode,
			buffer, sizeof(buffer), &length) != SQL_NO_DATA)
		{
			MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);
		}
		return FALSE;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return 0;
	}
	return TRUE;
}

void DBDisConnect()
{
	// 소멸,삭제, 뒷정리 등등 지우기,,,,
	// 삭제는 반대 순서로 해준다
	if (m_hStmt)SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	if (m_hDbc)SQLDisconnect(m_hDbc);
	if (m_hDbc)SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	if (m_hEnv)SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}

BOOL DBExecuteSQL()
{
	// 결과값을 돌려받기 위한 변수들
	SQLCHAR iUserID[21];
	SQLLEN IUSERID;

	// 결과를 돌려받기 위해 바인딩 한다.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, iUserID, sizeof(iUserID), &IUSERID);

	// SQL문을 실행한다.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR *)_T("select name from KHJUser"), SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// 읽어온 데이터 출력
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)iUserID);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}

// 현재 선택된 레코드를 읽어 에디트에 출력한다.
BOOL ReadRecord()
{
	// 결과값을 돌려받기 위한 변수들
	SQLTCHAR UserID[21];
	int iUserPS;
	BOOL bCreateID;
	SQLLEN IUSERID, IUSERPS, ICREATETIME;
	int idx;
	TCHAR key[256], szSQL[256];

	idx = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
		return FALSE;
	SendMessage(hList, LB_GETTEXT, idx, (LPARAM)key);
	wsprintf(szSQL, _T("select UserId,UserPs,CreateID from KHJUser where UserId='%s'"), key);

	// 결과를 돌려받기 위해 바인딩한다.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, UserID, sizeof(UserID), &IUSERID);
	SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &iUserPS, 0, &IUSERPS);
	SQLBindCol(m_hStmt, 3, SQL_C_ULONG,&bCreateID ,0, &ICREATETIME);

	// SQL문을 실행한다.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// 읽어온 데이터 출력
	if (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		SetWindowText(hUserID, (LPCTSTR)UserID);
		wsprintf(szSQL, _T("%d"), iUserPS);
		SetWindowText(hUserPS, szSQL);
		SendMessage(hCreateTime, BM_SETCHECK, (bCreateID ? BST_CHECKED : BST_UNCHECKED), 0);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}

// 레코드를 추가한다.
void AddRecord()
{
	SQLCHAR UserID[21];
	int iUserPS;
	BOOL bCreateID;
	TCHAR szSQL[256];

	// 값읽음
	GetWindowText(hUserID, (LPTSTR)UserID, 20);
	if (lstrlen((LPCTSTR)UserID) == 0)
	{
		MessageBox(hDlgMain, _T("추가할 레코드의 이름을 먼저 입력하십시요"), _T("알림"), MB_OK);
		return;
	}
	GetWindowText(hUserPS, szSQL, 256);


	iUserPS = _ttoi(szSQL);
	bCreateID = (SendMessage(hCreateTime, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Insert into KHJUser (UserId,UserPs,CreateID) VALUES('%s',%d,%d)"),
		UserID, iUserPS, bCreateID);

	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		MessageBox(hDlgMain, _T("레코드 추가 에러, 이름이 같은 레코드는 추가할 수 없습니다"), _T("에러"), MB_OK);
		return;
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// 선택된 레코드를 삭제한다.
void DeleteRecord()
{
	TCHAR Key[256], szSQL[256];
	int idx;

	idx = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		MessageBox(hDlgMain, _T("삭제할 레코드를 먼저 선택하십시요"), _T("알림"),MB_OK);
		return;
	}
	SendMessage(hList, LB_GETTEXT, idx, (LPARAM)Key);
	wsprintf(szSQL, _T("DELETE form KHJUser where UserId='%s'"), Key);

	if(SQLExecDirect(m_hStmt,(SQLTCHAR*)szSQL,SQL_NTS)!=SQL_SUCCESS)
	{
		return;
	}
	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// 업데이트 한다.
void UpdateRecord()
{
	SQLCHAR OldUserID[21], NewUserID[21];
	int iUserPS;
	BOOL bCreateID;
	TCHAR szSQL[256];
	int idx;

	// 값 읽음
	idx = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		return;
	}
	SendMessage(hList, LB_GETTEXT, idx, (LPARAM)OldUserID);

	GetWindowText(hUserID, (LPTSTR)NewUserID, 20);
	if (lstrlen((LPCTSTR)NewUserID) == 0)
	{
		MessageBox(hDlgMain, _T("변경할 레코드의 이름을 먼저 입력하십시요"), _T("알림"), MB_OK);
		return;
	}
	GetWindowText(hUserPS, szSQL, 256);
	iUserPS = _ttoi(szSQL);
	bCreateID = (SendMessage(hCreateTime, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Update KHJUser set UserId='%s', UserPs=%d, CreateID=%d where UserId='%s'"),
		NewUserID, iUserPS, bCreateID, OldUserID);

	if(SQLExecDirect(m_hStmt,(SQLTCHAR*)szSQL,SQL_NTS))
	{
		return;
	}
	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

void CenterWindow(HWND hWnd)
{
	RECT rcTemp1, rcTemp2;
	LONG iX, iY, iWidth, iHeight;

	GetWindowRect(GetDesktopWindow(), &rcTemp1);
	GetWindowRect(hWnd, &rcTemp2);

	iWidth = rcTemp2.right - rcTemp2.left;
	iHeight = rcTemp2.bottom - rcTemp2.top;
	iX = LONG((rcTemp1.right - iWidth) / 2);
	iY = LONG((rcTemp1.bottom - iHeight) / 2);
	MoveWindow(hWnd, iX, iY, iWidth, iHeight, TRUE);
}

LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		hList = GetDlgItem(hDlgMain, IDC_LISTUSER);
		hUserID = GetDlgItem(hDlgMain, IDC_FUserID);
		hUserPS = GetDlgItem(hDlgMain, IDC_FUserPS);
		hCreateTime = GetDlgItem(hDlgMain, IDC_FCreateTime);
		CenterWindow(hDlg);
		DBExecuteSQL();
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlgMain, IDOK);
			return TRUE;
		case IDC_BTNADD:
			AddRecord();
			return TRUE;
		case IDC_BTNDEL:
			DeleteRecord();
			return TRUE;
		case IDC_BTNUPDATE:
			UpdateRecord();
			return TRUE;
		case IDC_LISTUSER:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				ReadRecord();
				return TRUE;
			}
		}
		return FALSE;
	}
	return FALSE;
}

