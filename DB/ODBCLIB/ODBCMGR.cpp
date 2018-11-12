#include "ODBCMGR.h"

BOOL ODBCMGR::DBExecuteSQL()
{
	DBINFO info;

	// 결과를 돌려 받기 위해 바인딩한다.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, info.Name, sizeof(info.Name), &info.INFO_UserID);

	// SQL문을 실행 한다.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)_T("select name from KHJUser"), SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// 읽어온 데이터 출력
	SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
	while (SQLFetch(m_hList)!= SQL_NO_DATA)
	{
		SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)info.Name);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}
// 현재 선택된 레코드를 읽어 에디트에 출력한다.
BOOL ODBCMGR::ReadRecord()
{
	// 결과값 돌려받기 위한 변수들
	DBINFO info;
	int idx;
	TCHAR key[256], szSQL[256];

	idx = SendMessage(m_hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
		return FALSE;
	SendMessage(m_hList, LB_GETTEXT, idx, (LPARAM)key);
	wsprintf(szSQL, _T("select UserId, UserPs, CreateID from KHJUser where name = '%s'"), key);

	// 결과를 돌려받기 위해 바인딩한다.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, info.Name, sizeof(info.Name),&info.INFO_UserID);
	SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &info.PS, 0, &info.INFO_UserPS);
	SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &info.CreateID, 0, &info.INFO_CreateID);

	// SQL문을 실행한다.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS)!=SQL_SUCCESS)
	{
		return FALSE;
	}

	// 읽어온 데이터 출력
	if (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		SetWindowText(m_hUserID, (LPCTSTR)info.Name);
		wsprintf(szSQL, _T("%d"), info.PS);
		SetWindowText(m_hUserPS, szSQL);
		SendMessage(m_hCreateID, BM_SETCHECK, (info.CreateID ? BST_CHECKED : BST_UNCHECKED), 0);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}

// 레코드를 추가한다.
void ODBCMGR::AddRecord()
{
	DBINFO	info;
	TCHAR szSQL[256];
	
	// 값 읽음
	GetWindowText(m_hUserID, (LPTSTR)info.Name, 20);
	if (lstrlen((LPCTSTR)info.Name) == 0)
	{
		MessageBox(m_hDlgMain, _T("추가할 레코드의 이름을 먼저 입력하십시요"), _T("알림"), MB_OK);
		return;
	}
	GetWindowText(m_hUserPS, szSQL, 256);

	info.PS = _ttoi(szSQL);
	info.CreateID = (SendMessage(m_hUserPS, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Insert into KHJUser(UserId, UserPs, CreateID)VALUES('%s',%d,%d)"),
		info.Name, info.PS, info.CreateID);

	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		MessageBox(m_hDlgMain, _T("레코드 추가 에러. 이름이 같은 레코드는 추가할 수 없습니다."), _T("에러"), MB_OK);
		return;
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// 선택된 레코드를 삭제한다.
void ODBCMGR::DeleteRecord()
{
	TCHAR key[256], szSQL[256];
	DBINFO info;
	int idx;

	idx = SendMessage(m_hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		MessageBox(m_hDlgMain, _T("삭제할 레코드를 먼저 선택하십시요"), _T("알림"), MB_OK);
		return;
	}
	SendMessage(m_hList, LB_GETTEXT, idx, (LPARAM)key);
	wsprintf(szSQL, _T("Delete form KHJUser where UserId = '%s'"), key);

	if(SQLExecDirect(m_hStmt,(SQLTCHAR *)szSQL,SQL_NTS)!=SQL_SUCCESS)
	{
		return;
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// 업데이트 한다
void ODBCMGR::UpdateRecord()
{
	DBINFO info;
	SQLCHAR OldName[21], NewName[21];
	TCHAR szSQL[256];
	int idx;
	
	// 값 읽음 
	idx = SendMessage(m_hList, LB_GETTEXT, 0,0);
	if (idx == -1)
	{
		return;
	}
	GetWindowText(m_hUserID, (LPTSTR)NewName, 20);
	if (lstrlen((LPCTSTR)NewName) == 0)
	{
		MessageBox(m_hDlgMain, _T("변경할 레코드의 이름을 먼저 입력하십시요"), _T("알림"), MB_OK);
		return;
	}
	GetWindowText(m_hUserPS, szSQL, 256);
	info.PS = _ttoi(szSQL);
	info.CreateID=(SendMessage(m_hUserPS, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Update KHJUser set UserId = '%s', UserPs = %d, CreateID='%d' where UserId = '%s'"),
		NewName, info.PS, info.CreateID, OldName);

	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS))
	{
		return;
	}
	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}
ODBCMGR::ODBCMGR()
{
}


ODBCMGR::~ODBCMGR()
{
}
