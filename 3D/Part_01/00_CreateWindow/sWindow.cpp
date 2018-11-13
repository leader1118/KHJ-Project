#include "sWindow.h"

sWindow* g_pWindow = NULL; // �����Լ�

// ���� ������ ���ν���
LRESULT CALLBACK StaticWndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

// ������ ���ν���
LRESULT sWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc; // �ڵ�

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

void sWindow::CenterWindow(HWND hwnd)
{
	// ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�
	int iScreenWindth = GetSystemMetrics(SM_CXFULLSCREEN); // ���� ������
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN); // ���� ������

	// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
	int iDestX = (iScreenWindth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2; // ���λ����� - ������ ���� ������ - ������ ���� ���� ������ 2
	int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2; // ���λ����� - ������ ���� �ϴ� - ������ ���� ��� ������ 2

	// �����츦 ȭ�� �߾����� �̵���Ų��.
	MoveWindow(hwnd, iDestX, iDestY, // �ڵ�, ������â ���ΰ�, ���ΰ�, ������ ���� ���� ��, ���ΰ�
		m_rcWindowBounds.right - m_rcWindowBounds.left, // ������ ���� ���ΰ� = ������ ���� ������ - ����
		m_rcWindowBounds.bottom - m_rcWindowBounds.top, // ������ ���� ���ΰ� = ������ ���� �ϴ� - ���
		true);
}

bool sWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, TCHAR* strWindowTitle)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ������ Ŭ������ ��Ÿ���� ����
	wcex.lpfnWndProc = &StaticWndproc; // �޽��� ó�� �Լ� ����
	wcex.cbClsExtra = 0; // ������ �޸𸮾��� ����Ʈ ������ ����
	wcex.cbWndExtra = 0; // ���������쿡�� ����ϰ��� �ϴ� ������ �޸𸮾��� ����
	wcex.hInstance = hInstance; // ������ Ŭ������ ����� ���� ���α׷��� �ν��Ͻ� �ڵ� 
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)); // �������� ����
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ���� ����
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��׶��� ����
	wcex.lpszMenuName = NULL; // �޴� ����
	wcex.lpszClassName = L"KHJWindow"; // ����ϰ��� �ϴ� ������ �̸�
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if(!RegisterClassEx(&wcex))
	{
		return false;
	}
}
sWindow::sWindow()
{
}


sWindow::~sWindow()
{
}
