#include "Window.h"
Window* g_pWindow = 0;
HWND g_hWnd = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow != NULL);
	LRESULT ret;
	if (ret = g_pWindow->MsgProc(hWnd, msg, wParam, lParam))
	{
		return ret;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//MessageBox(NULL, L"윈도우가 떴다.", L"윈도우생성", MB_OK);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);// WM_QUIT--> PUSH			
	}return 0;
	}
	return 0;
}
void Window::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}
bool Window::SetWindow(HINSTANCE	hInst,
	const TCHAR* pTitleName,
	UINT iWidth, UINT iHeight)
{
	m_hInstance = hInst;
	// 윈도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = L"MyWindow";
	wc.hCursor = LoadCursor(m_hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (RegisterClassEx(&wc) == FALSE)
	{
		return false;
	}

	//// 윈도우 생성( 등록된 클래스를 사용해서 )
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"MyWindow", pTitleName,
		m_dwStyle,
		0, 0, iWidth, iHeight,
		NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL)
	{
		return false;
	}
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
void Window::Set(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}
void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHegiht = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHegiht - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtWindow.right, m_rtWindow.bottom, true);
}
bool Window::Run()
{
	if (!GameInit()) return false;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
			MsgEvent(msg);
		}
		else
		{
			GameRun();
			Sleep(1);
		}
	}
	return GameRelease();
}
bool Window::GameInit()
{
	return true;
}
bool Window::GameRun() {
	return true;
}
bool Window::GameRelease() {
	return true;
}
Window::Window()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	g_pWindow = this;
}


Window::~Window()
{
}
