// UI_INTERFACE.cpp: 구현 파일
//

#include "stdafx.h"
#include "UI_TOOL.h"
#include "UI_INTERFACE.h"
#include "afxdialogex.h"


// UI_INTERFACE 대화 상자

IMPLEMENT_DYNAMIC(UI_INTERFACE, CDialog)

UI_INTERFACE::UI_INTERFACE(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_INTERFACE, pParent)
{

}

UI_INTERFACE::~UI_INTERFACE()
{
}

void UI_INTERFACE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UI_INTERFACE, CDialog)
ON_WM_SIZE()
//ON_BN_CLICKED(IDC_BUTTON5, &UI_INTERFACE::OnBnClickedButton5)
END_MESSAGE_MAP()


// UI_INTERFACE 메시지 처리기




void UI_INTERFACE::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd* pCtl = GetDlgItem(IDD_INTERFACE);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (!pCtl) { return; }

	CRect rect;
	pCtl->GetWindowRect(&rect);
	ScreenToClient(&rect);

	pCtl->MoveWindow(rect.left, rect.top, cx - 2 * rect.left, cy - rect.top - rect.left, TRUE);

	return;	
}

