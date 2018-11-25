#pragma once

#include "xDevice.h"
class xWindow : public xDevice // 디바이스를 상속받는다
{
public:
	HWND		m_hWnd; // 윈도우 핸들
	HINSTANCE	m_hInstance; // 핸들 인스턴스
	RECT		m_rtClient; // 영역 렉트
	RECT		m_rtWindow; // 윈도우 렉트
private:
	DWORD		m_dwStyle; //unsinged long
public:
	void		Set(DWORD dwStyle);
	void		CenterWindow(); // 윈도우 센터를 잡아준다
	bool		SetWindow(HINSTANCE	hInstance, // 윈도우 세팅
		const TCHAR* pTitleName = L"KHJ Sample",
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
	xWindow();
	virtual ~xWindow();
};

