#include <Windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

DWORD m_dwKeyState[255];
int   g_iFPS = 0;
int   g_iTmpCount = 0;
float g_fSecPerFrame = 0.0f;
float g_fGameTime = 0.0f;
TCHAR g_szBuffer[256];

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // 운영체제
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);

}

int WINAPI wWinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPWSTR IpCmdLine,
	int nCmdShow)
{


	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MYWINDOW";
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, L"MYWINDOW", L"WINDOW TEST",
		WS_OVERLAPPEDWINDOW,
		0, 0, 800, 600,      //위치 위치 , 해상도 해상도
		NULL, NULL, hInst, NULL);
	if (hWnd == NULL)
		return false;
	ShowWindow(hWnd, SW_SHOW);

	HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"end04.bmp.bmp", IMAGE_BITMAP,
		0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	HDC hdc = GetDC(hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	//세팅
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	DWORD dwTick = timeGetTime();

	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//블럭형 함수
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			//Sleep(1);

			WORD dwCurrentTick = timeGetTime();
			DWORD dwElapseTick = dwCurrentTick - dwTick;

			g_fSecPerFrame = dwElapseTick / 1000.0f;
			g_fGameTime += g_fSecPerFrame;
			static float fTime = 0.0f;
			fTime += g_fSecPerFrame;
			if (fTime >= 1.0f)
			{
				g_iFPS = g_iTmpCount;
				fTime -= 1.0f;
				g_iTmpCount = 0;
			}
			dwTick = dwCurrentTick;

			/*static DWORD dw100Frame = 0;
			dw100Frame += dwElapseTick;
			if (dw100Frame < 10)
			{
			continue;
			}
			dw100Frame = 0;*/

			for (int iKey = 0; iKey < 255; iKey++)
			{
				SHORT sKey = GetAsyncKeyState(iKey);
				m_dwKeyState[iKey] = (sKey & 0x8000) ? 1 : 0;
			}
			if (m_dwKeyState[VK_LBUTTON])
			{
				MessageBox(NULL, L"VK_LBUTTON", L"MOUSE", MB_OK);
			}
			if (m_dwKeyState['W'])
			{
				MessageBox(NULL, L"W", L"MOUSE", MB_OK);
			}
			if (m_dwKeyState[VK_LCONTROL] &&
				m_dwKeyState[VK_RBUTTON])
			{
				MessageBox(NULL, L"CONBO", L"KEY+MOUSE", MB_OK);
			}

			_stprintf_s(g_szBuffer, L"%d : %10.4f : %10.4f :", g_iFPS, g_fGameTime, g_fSecPerFrame);

			BitBlt(
				//출력 DC
				hdc, 0, 0, 800, 600,
				//소스 (원본,dc)
				hMemDC, 0, 0, SRCCOPY);
			TextOut(hdc, 0, 0, g_szBuffer, wcslen(g_szBuffer));

			g_iTmpCount++;

		}
	}
	//복원
	SelectObject(hMemDC, hBitmap);

	DeleteObject(hBitmap);
	ReleaseDC(hWnd, hMemDC);
	ReleaseDC(hWnd, hdc);
	return true;
}
