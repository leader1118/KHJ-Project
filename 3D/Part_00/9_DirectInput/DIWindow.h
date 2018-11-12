#pragma once
#include "DIDevice.h"
class DIWindow: public DIDevice
{
public:
	////////////////////////////////////////////////////////////
	// Global Variables
	////////////////////////////////////////////////////////////
	HINSTANCE		m_hInstance; // �ν��Ͻ� �ڵ�
	HWND			m_hWnd; // ������ �ڵ�
	DWORD			m_dwWindowStyle; // ������ ��Ÿ��
	RECT			m_rcWindowBounds; // ������ ����
	RECT			m_rcWindowClient; // Ŭ���̾�Ʈ ����
	UINT			m_iWindowWidth; // Ŭ���̾�Ʈ ���� ����ũ��
	UINT			m_iWindowHeight; // Ŭ���̾�Ʈ ���� ����ũ��
	bool			m_bActive;		// �������� Ȱ��ȭ ���θ� �Ǵ��Ѵ�.
public:
	 // ������ ����
	bool InitWindow(HINSTANCE hInstance, int nCmdShow, TCHAR* strWindowTitle, BOOL IsFullScreen = FALSE);
	// ������ ��ġ ȭ�� �߾����� �̵�
	void CenterWindow(HWND hwnd);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool Run();
	virtual LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	DIWindow(void);
	virtual ~DIWindow(void);
};

