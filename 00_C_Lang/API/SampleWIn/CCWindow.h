#pragma once
#include "STD.h"

class CCWindow
{
public:
	HWND		m_hWnd; // window �ڵ�
	HINSTANCE	m_hInstance; //���ఴü �ڵ�
	RECT		m_rtWindow;
	RECT		m_rtClient;
public:
	void		CenterWindow();
	bool		SetWindow(HINSTANCE hInstance,
		TCHAR* pTitleName,
		int iWidth = 800, int iHeight = 600);
	bool		Run();
	bool		Release();
	virtual bool	GameRun() { return true; };
	virtual void	MsgEvent(MSG msg) {};
	virtual	bool	GameInit() { return true; };
	virtual bool	GameRelease() { return true; };
public:
	CCWindow();
	virtual ~CCWindow();
};

