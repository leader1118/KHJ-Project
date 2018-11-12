#include "ODBCMGR.h"

BOOL ODBCMGR::DBExecuteSQL()
{
	DBINFO info;

	// ����� ���� �ޱ� ���� ���ε��Ѵ�.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, info.Name, sizeof(info.Name), &info.INFO_UserID);

	// SQL���� ���� �Ѵ�.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)_T("select name from KHJUser"), SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	// �о�� ������ ���
	SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
	while (SQLFetch(m_hList)!= SQL_NO_DATA)
	{
		SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)info.Name);
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	return TRUE;
}
// ���� ���õ� ���ڵ带 �о� ����Ʈ�� ����Ѵ�.
BOOL ODBCMGR::ReadRecord()
{
	// ����� �����ޱ� ���� ������
	DBINFO info;
	int idx;
	TCHAR key[256], szSQL[256];

	idx = SendMessage(m_hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
		return FALSE;
	SendMessage(m_hList, LB_GETTEXT, idx, (LPARAM)key);
	wsprintf(szSQL, _T("select UserId, UserPs, CreateID from KHJUser where name = '%s'"), key);

	// ����� �����ޱ� ���� ���ε��Ѵ�.
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, info.Name, sizeof(info.Name),&info.INFO_UserID);
	SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &info.PS, 0, &info.INFO_UserPS);
	SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &info.CreateID, 0, &info.INFO_CreateID);

	// SQL���� �����Ѵ�.
	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS)!=SQL_SUCCESS)
	{
		return FALSE;
	}

	// �о�� ������ ���
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

// ���ڵ带 �߰��Ѵ�.
void ODBCMGR::AddRecord()
{
	DBINFO	info;
	TCHAR szSQL[256];
	
	// �� ����
	GetWindowText(m_hUserID, (LPTSTR)info.Name, 20);
	if (lstrlen((LPCTSTR)info.Name) == 0)
	{
		MessageBox(m_hDlgMain, _T("�߰��� ���ڵ��� �̸��� ���� �Է��Ͻʽÿ�"), _T("�˸�"), MB_OK);
		return;
	}
	GetWindowText(m_hUserPS, szSQL, 256);

	info.PS = _ttoi(szSQL);
	info.CreateID = (SendMessage(m_hUserPS, BM_GETCHECK, 0, 0) == BST_CHECKED);
	wsprintf(szSQL, _T("Insert into KHJUser(UserId, UserPs, CreateID)VALUES('%s',%d,%d)"),
		info.Name, info.PS, info.CreateID);

	if (SQLExecDirect(m_hStmt, (SQLTCHAR*)szSQL, SQL_NTS) != SQL_SUCCESS)
	{
		MessageBox(m_hDlgMain, _T("���ڵ� �߰� ����. �̸��� ���� ���ڵ�� �߰��� �� �����ϴ�."), _T("����"), MB_OK);
		return;
	}

	if (m_hStmt)SQLCloseCursor(m_hStmt);
	DBExecuteSQL();
}

// ���õ� ���ڵ带 �����Ѵ�.
void ODBCMGR::DeleteRecord()
{
	TCHAR key[256], szSQL[256];
	DBINFO info;
	int idx;

	idx = SendMessage(m_hList, LB_GETCURSEL, 0, 0);
	if (idx == -1)
	{
		MessageBox(m_hDlgMain, _T("������ ���ڵ带 ���� �����Ͻʽÿ�"), _T("�˸�"), MB_OK);
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

// ������Ʈ �Ѵ�
void ODBCMGR::UpdateRecord()
{
	DBINFO info;
	SQLCHAR OldName[21], NewName[21];
	TCHAR szSQL[256];
	int idx;
	
	// �� ���� 
	idx = SendMessage(m_hList, LB_GETTEXT, 0,0);
	if (idx == -1)
	{
		return;
	}
	GetWindowText(m_hUserID, (LPTSTR)NewName, 20);
	if (lstrlen((LPCTSTR)NewName) == 0)
	{
		MessageBox(m_hDlgMain, _T("������ ���ڵ��� �̸��� ���� �Է��Ͻʽÿ�"), _T("�˸�"), MB_OK);
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
