#pragma once


// UI_INTERFACE 대화 상자

class UI_INTERFACE : public CDialog
{
	DECLARE_DYNAMIC(UI_INTERFACE)

public:
	UI_INTERFACE(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UI_INTERFACE();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INTERFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnBnClickedButton5();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnBnClickedButton4();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
