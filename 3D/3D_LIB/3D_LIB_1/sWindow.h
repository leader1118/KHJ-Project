#pragma once
#include "sDevice.h"
class sWindow : public sDevice
{
public:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_rtClient;
	RECT		m_rtWindow;
public:
	DWORD m_dwStyle;
public:
	void		Set(DWORD dwStyle);
	void		CenterWindow();
	bool		SetWindow(HINSTANCE	hInstance,
		const TCHAR* pTitleName = L"KHJ",
		UINT iWidth = 800, UINT iHeight = 600);
	bool		Run();
public:
	virtual LRESULT	MainMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool	GameInit();
	virtual bool	GameRun();
	virtual bool	GameRelease();

	void MsgEvent(MSG msg);
public:
	sWindow();
	virtual ~sWindow();
};

