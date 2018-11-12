#include "DXWindow.h"

DXWindow* g_pWindow = NULL;
// ----------------------------------------------
// ���� ������ ���ν���
// ----------------------------------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

// ---------------------------------------------
// ������ ���ν���
// ---------------------------------------------
LRESULT DXWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
void DXWindow::CenterWindow(HWND hwnd)
{
	// ȭ�� ��ũ���� �ػ� (���̿� ����)�� ��´�.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
	int iDestX = (iScreenWidth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2;

	//d �����츦 ȭ�� �߾����� �̵���Ų��.
	MoveWindow(hwnd, iDestX, iDestY,
		m_rcWindowBounds.right - m_rcWindowBounds.left,
		m_rcWindowBounds.bottom - m_rcWindowBounds.top,
		true);
}
bool DXWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* strWindowTitle)
{
	//Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TBASIS3D11_Sample";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return false;

	//Create window
	m_hInstance = hInstance;
	RECT rc = { 0,0,800,600 };
	// �۾� ����(Ÿ��Ʋ ��/��輱/�޴�/��ũ�� �� ���� ������ ������ ����), ������ ��Ÿ�� ,�޴� ����
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,//ws_EX_TOPMOST,//|WS_EX_TOOLWINDOW,
		L"TBASIS3D11_Sample", strWindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);

	if (!m_hWnd)
		return false;
	
	// ������ ��Ÿ���� �����ϰ� ��ũ�� ������ Ŭ���̾�Ʈ ������ ��´�.
	m_dwWindowStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	GetWindowRect(m_hWnd, &m_rcWindowBounds);
	GetClientRect(m_hWnd, &m_rcWindowClient);

	CenterWindow(m_hWnd);
	UpdateWindow(m_hWnd);

	// ������ Ŭ���̾�Ʈ ���̿� ���̸� ��´�.
	m_iWindowWidth = m_rcWindowClient.right - m_rcWindowClient.left;
	m_iWindowHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

	ShowWindow(m_hWnd, nCmdShow);
	return true;
}
bool	DXWindow::Init()
{
	return true;
}
bool	DXWindow::Frame()
{
	return true;
}
bool	DXWindow::Render()
{
	return true;
}
bool DXWindow::Release()
{
	return true;
}
bool DXWindow::Run()
{
	if (!Init())return false;
	// Main message loop
	MSG msg={ 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!Frame() || !Render())
			{
				break;
			}
		}
	}
	if (!Release())return false;
	return true;
}
DXWindow::DXWindow(void)
{
	m_hInstance = NULL;
	m_hWnd = NULL;
	g_pWindow = this;
}


DXWindow::~DXWindow(void)
{
}
