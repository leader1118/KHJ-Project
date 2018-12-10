#include "S_Window.h"
#include "S_Input.h"

S_Window* g_Window=NULL;
RECT	  g_rtClient;
HWND	  g_hWnd;
HINSTANCE g_hInstance;


LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (g_Window->MsgProc(hWnd, msg,
		wParam, lParam) > 0)
	{
		return 0;
	}

	switch (msg)
	{
	case WM_SIZE:
	{
		
		if (wParam != SIZE_MINIMIZED && g_Window != NULL)
		{
			UINT width = LOWORD(lParam); 
			UINT height = HIWORD(lParam);
			g_Window->ResizeClient(width, height);
		}
	}break;
	
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT S_Window::MsgProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	return 0;
}

void S_Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	RECT rt = { 0,0,m_rtWindow.right, m_rtWindow.bottom };
	
	AdjustWindowRect(&rt, GetWindowStyle(m_hWnd), FALSE);

	MoveWindow(m_hWnd, x, y,
		rt.right - rt.left,
		rt.bottom - rt.top, true);
}
bool	S_Window::ResizeClient(UINT iWidth, UINT iHeight)
{
	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	return true;
}

bool	S_Window::SetWindow(HINSTANCE hInstance,
	const  TCHAR* pTitleName,
	int iWidth, int iHeight,
	DWORD dwStyle)
{
	m_hInstance = hInstance;
	g_hInstance = m_hInstance;
	//1, 윈도우 클래스 객체 등록(운영체제)
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 프로시져
	wc.lpfnWndProc = WndProc,//WNDPROC     lpfnWndProc;
		wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDC_IBEAM);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Chat_KHJ",
		wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	//2, 등록된 클래스 객체를 사용하여 윈도우 생성	
	RECT rt = { 0,0,iWidth, iHeight };
	AdjustWindowRect(&rt, dwStyle, FALSE);
	m_rtClient = rt;
#ifdef _DEBUG
	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,//DWORD dwExStyle,
		L"Chat_KHJ",// LPCWSTR lpClassName,
		pTitleName,//LPCWSTR lpWindowName,
		dwStyle
		,//DWORD dwStyle,
		0, 0,
		rt.right - rt.left,
		rt.bottom - rt.top,
		NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL) return false;
	g_hWnd = m_hWnd;
#else
	m_hWnd = CreateWindowEx(
		WS_EX_TOPMOST,//DWORD dwExStyle,
		L"Chat_KHJ",// LPCWSTR lpClassName,
		pTitleName,//LPCWSTR lpWindowName,
		WS_POPUPWINDOW,//DWORD dwStyle,
		0, 0, iWidth, iHeight,
		NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL) return false;
#endif
	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
};
bool	S_Window::Run()
{
	GameInit();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (true)
	{
		if (S_INPUT.OnceKeyUp(VK_ESCAPE))
		{
			break;
		}

		// PM_NOREMOVE, PM_REMOVE
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
		}
	}
	GameRelease();
	return true;
};
bool S_Window::Release()
{
	return true;
};
S_Window::S_Window()
{
	g_Window = this;
}


S_Window::~S_Window()
{
}
