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

// �ڵ�
SQLHENV m_hEnv;   // ȯ���ڵ�
SQLHDBC m_hDbc;   // �����ڵ�
SQLHSTMT m_hStmt; // ����ڵ�

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
		MessageBox(NULL, _T("������ ���̽��� ������ �� �����ϴ�"), _T("����"), MB_OK);
		return 0;
	}

	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOGMAIN), HWND_DESKTOP, (DLGPROC)MainDlgProc);

	DBDisConnect();
	return 0;
}

// ���� �߻��� ���� ������ ����� �ش�.
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
		wsprintf(str, _T("SQLSTATE: %s, ��������:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("���� ����"), 0);
		ii++;
	}
}
BOOL DBConnect()
{
	// ���� ������ ���� ������
	TCHAR InCon[255];
	SQLTCHAR OutCon[1024];
	SQLSMALLINT cbOutCon;
	TCHAR Dir[MAX_PATH];
	SQLRETURN Ret;

	// ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) // �ڵ��� �Ҵ��Ѵ�
	{
		return FALSE;
	}
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) // �ڵ��� �����Ӽ��� ���Ѵ�
	{
		return FALSE;
	}
	// ���� �ڵ��� �Ҵ��ϰ� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return FALSE;
	}
	// MDB ���Ͽ� �����ϱ�
	GetCurrentDirectory(MAX_PATH, Dir);
	// ���� --> *.mdb,"��ĭ�پ�� �Ѵ�." *.accdb
	// <*accdb> ����
	// _stprintf(InCon,_T("DRIVER={Microsoft Access Driver(*.mdb, *.accdb)}; DBQ=%s\\cigarette.accdb;"),Dir);
	//// <*.mdb> ����
	// _stprintf(InCon, _T(DRIVER={Microsoft Access Driver(*.mdb, *.accdb)}; DBQ=%s\\cigarette.mdb;"),Dir);
	//// <*.dsn> ����
	// _stprintf((TCHAR*))InCon, _T("FileDsn=%s"),_T("cigaretteaccdb.dsn"));
	// _stprintf((THCAR*)InCon,_T("Dsn=%s"),_T("SVRKGCA"));
	
	// SQLSERVER(client) ����
	_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=112.216.123.139,1433;Network=dbmssocn;Database=KHJDB;Uid=sa;Pwd=kgca!@34;"));
	Ret = SQLDriverConnect(m_hDbc, NULL, (SQLTCHAR*)InCon, _countof(InCon), OutCon,
		_countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);
	
	Ret = SQLConnect(m_hDbc,
		(SQLTCHAR*)L"KHJUser", SQL_NTS,		// ���̺� �̸�
		(SQLTCHAR*)L"sa", SQL_NTS,			
		(SQLTCHAR*)L"kgca!@34", SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER sqlcode;
		SQLSMALLINT length;
		// �ܼ��� ����
		SQLError(m_hEnv, m_hDbc, m_hStmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
		MessageBox(NULL, (LPTSTR)buffer, (LPTSTR)sqlstate, MB_OK);  // MB_OK = ok ��ư �ϳ��� ��Ÿ����

		// ��� ���� ������
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
	// �Ҹ�,����, ������ ��� �����,,,,
	// ������ �ݴ� ������ ���ش�
	if (m_hStmt)SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	if (m_hDbc)SQLDisconnect(m_hDbc);
	if (m_hDbc)SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	if (m_hEnv)SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}

BOOL DBExecuteSQL()
{
	// ������� �����ޱ� ���� ������
	SQLCHAR iUserID[21];
	SQLLEN IUSERID;

	// ����� �����ޱ� ���� ���ε� �Ѵ�.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, iUserID, sizeof(iUserID), &IUSERID);

	// SQL���� �����Ѵ�.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR *)_T("select name from KHJUser"), SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// �о�� ������ ���
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)iUserID);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}

// ���� ���õ� ���ڵ带 �о� ����Ʈ�� ����Ѵ�.
BOOL ReadRecord()
{
	// ������� �����ޱ� ���� ������
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

	// ����� �����ޱ� ���� ���ε��Ѵ�.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, UserID, sizeof(UserID), &IUSERID);
	SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &iUserPS, 0, &IUSERPS);
	SQLBindCol(m_hStmt, 3, SQL_C_ULONG,&bCreateID ,0, &ICREATETIME);

	// SQL���� �����Ѵ�.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// �о�� ������ ���
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

// ���ڵ带 �߰��Ѵ�.
void AddRecord()
{
	SQLCHAR UserID[21];
	int iUserPS;
	BOOL bCreateID;
	TCHAR szSQL[256];

	// ������
	GetWindowText(hUserID, (LPTSTR)UserID, 20);
	if (lstrlen((LPCTSTR)UserID) == 0)
	{
		MessageBox(hDlgMain, _T("�߰��� ���ڵ��� �̸��� ���� �Է��Ͻʽÿ�"), _T("�˸�"), MB_OK);
		return;
	}
	GetWindowText(hUserPS, szSQL, 256);


	iUserPS = _ttoi(szSQL);
	bCreateID = (SendMessage(hCreateTime, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Insert into KHJUser (UserId,UserPs,CreateID) VALUES('%s',%d,%d)"),
		UserID, iUserPS, bCreateID);

	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		MessageBox(hDlgMain, _T("���ڵ� �߰� ����, �̸��� ���� ���ڵ�� �߰��� �� �����ϴ�"), _T("����"), MB_OK);
		return;
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// ���õ� ���ڵ带 �����Ѵ�.
void DeleteRecord()
{
	TCHAR Key[256], szSQL[256];
	int idx;

	idx = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		MessageBox(hDlgMain, _T("������ ���ڵ带 ���� �����Ͻʽÿ�"), _T("�˸�"),MB_OK);
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

// ������Ʈ �Ѵ�.
void UpdateRecord()
{
	SQLCHAR OldUserID[21], NewUserID[21];
	int iUserPS;
	BOOL bCreateID;
	TCHAR szSQL[256];
	int idx;

	// �� ����
	idx = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		return;
	}
	SendMessage(hList, LB_GETTEXT, idx, (LPARAM)OldUserID);

	GetWindowText(hUserID, (LPTSTR)NewUserID, 20);
	if (lstrlen((LPCTSTR)NewUserID) == 0)
	{
		MessageBox(hDlgMain, _T("������ ���ڵ��� �̸��� ���� �Է��Ͻʽÿ�"), _T("�˸�"), MB_OK);
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

