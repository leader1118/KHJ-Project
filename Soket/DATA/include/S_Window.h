#pragma once

#include "S_Std.h"

class S_Window
{
public:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_rtWindow;
	RECT		m_rtClient;
public:
	void		CenterWindow();

	bool	SetWindow(HINSTANCE hInstance,
		const TCHAR* pTitleName = L"Chat_KHJ",
		int iWidth = 800, int iHeight = 600,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW);
	bool	Run();
	bool	Release();
	virtual  bool   ResizeClient(UINT iWidth, UINT iHeight);
	virtual  bool	GameRun() { return true; };
	virtual  void   MsgEvent(MSG msg) {};
	virtual  bool	GameInit() { return true; };
	virtual  bool   GameRelease() { return true; };
	virtual LRESULT MsgProc(HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);
public:
	S_Window();
	virtual ~S_Window();
};

