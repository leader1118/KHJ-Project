#pragma once

#include "xDevice.h"
class xWindow : public xDevice // ����̽��� ��ӹ޴´�
{
public:
	HWND		m_hWnd; // ������ �ڵ�
	HINSTANCE	m_hInstance; // �ڵ� �ν��Ͻ�
	RECT		m_rtClient; // ���� ��Ʈ
	RECT		m_rtWindow; // ������ ��Ʈ
private:
	DWORD		m_dwStyle; //unsinged long
public:
	void		Set(DWORD dwStyle);
	void		CenterWindow(); // ������ ���͸� ����ش�
	bool		SetWindow(HINSTANCE	hInstance, // ������ ����
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

