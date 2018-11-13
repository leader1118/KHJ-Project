#include "sWindow.h"

sWindow* g_pWindow = NULL; // 전역함수

// 메인 윈도우 프로시져
LRESULT CALLBACK StaticWndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

// 윈도우 프로시져
LRESULT sWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc; // 핸들

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
	// 화면 스크린의 해상도(넓이와 높이)를 얻는다
	int iScreenWindth = GetSystemMetrics(SM_CXFULLSCREEN); // 가로 사이즈
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN); // 세로 사이즈

	// 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
	int iDestX = (iScreenWindth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2; // 가로사이즈 - 윈도우 영역 오른쪽 - 윈도우 영역 왼쪽 나누기 2
	int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2; // 세로사이즈 - 윈도우 영역 하단 - 윈도우 영역 상단 나누기 2

	// 윈도우를 화면 중앙으로 이동시킨다.
	MoveWindow(hwnd, iDestX, iDestY, // 핸들, 윈도우창 가로값, 세로값, 윈도우 영역 가로 값, 세로값
		m_rcWindowBounds.right - m_rcWindowBounds.left, // 윈도우 영역 가로값 = 윈도우 영역 오른쪽 - 왼쪽
		m_rcWindowBounds.bottom - m_rcWindowBounds.top, // 윈도우 영역 세로값 = 윈도우 영역 하단 - 상단
		true);
}

bool sWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, TCHAR* strWindowTitle)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 클래스의 스타일을 지정
	wcex.lpfnWndProc = &StaticWndproc; // 메시지 처리 함수 지정
	wcex.cbClsExtra = 0; // 여분의 메모리양을 바이트 단위로 지정
	wcex.cbWndExtra = 0; // 개별윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wcex.hInstance = hInstance; // 윈도우 클래스를 등록한 응용 프로그램의 인스턴스 핸들 
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)); // 아이콘을 지정
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서를 지정
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 백그라운드 색상
	wcex.lpszMenuName = NULL; // 메뉴 지정
	wcex.lpszClassName = L"KHJWindow"; // 등록하고자 하는 윈도우 이름
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
