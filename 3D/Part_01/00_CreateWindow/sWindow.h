#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>

class sWindow
{
public:
	HINSTANCE			m_hInstance; // �ν��Ͻ� �ڵ�
	HWND				m_hWnd;		 // ������ �ڵ�
	DWORD				m_dwWindowStyle; // ������ ��Ÿ��
	RECT				m_rcWindowBounds; // ������ ����
	RECT				m_rcWindowClient; // Ŭ���̾�Ʈ ����
	UINT				m_iWindowWidth;	  // Ŭ���̾�Ʈ ���� ����ũ��
	UINT				m_iWindowHeight;  // Ŭ���̾�Ʈ ���� ����ũ��
public:
	// ������ ����
	bool				InitWindow(HINSTANCE hInstance, int nCmdShow, TCHAR* strWindowTitle);
	// ������ ��ġ ȭ�� �߾����� �̵�
	void				CenterWindow(HWND hwnd);
public:
	virtual bool	 Init();	// �ʱ�ȭ
	virtual bool	 Frame();	// 
	virtual bool	 Render();	//
	virtual bool	 Release(); // �Ҹ�, ����
	virtual bool	 Run();		// 
	virtual LRESULT	 WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	sWindow(void);
	virtual ~sWindow(void);
};
