#pragma once
#include "DUtils.h"
#include "DXDevice.h"

class DXWindow : public DXDevice
{
public:
	//----------------------------
	//Global Variables
	//----------------------------
	HINSTANCE	m_hInstance;	// �ν��Ͻ� �ڵ�
	HWND		m_hWnd;			// ������ �ڵ�
	DWORD		m_dwWindowStyle; // ������ ��Ÿ��
	RECT		m_rcWindowBounds; // ������ ����
	RECT		m_rcWindowClient; // Ŭ���̾�Ʈ ����
	UINT		m_iWindowWidth;	// Ŭ���̾�Ʈ ���� ����ũ��
	UINT		m_iWindowHeight;// Ŭ���̾�Ʈ ���� ����ũ��
public:
	// ������ ����
	bool		InitWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* strWindowTitle);
	// ������ ��ġ ȭ�� �߾����� �̵�
	void		CenterWindow(HWND hwnd);
public:
	virtual		bool	Init();
	virtual		bool	Frame();
	virtual		bool	Render();
	virtual		bool	Release();
	virtual		bool	Run();
	virtual		LRESULT	WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	DXWindow(void);
	virtual ~DXWindow(void);
};

