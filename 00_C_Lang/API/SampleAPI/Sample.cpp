#include <Windows.h>
#include <tchar.h>
#pragma comment (lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam,
	LPARAM lParam)
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
	LPWSTR lpCmdLine,
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
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, L"MYWINDOW",L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,
		0,0,800,600,
		NULL,NULL,hInst,NULL);
	if (hWnd == NULL)
		return false;
	ShowWindow(hWnd, SW_SHOW);

	HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"end04.bmp.bmp",
		IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	HDC hdc = GetDC(hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	

	MSG msg;
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
		}
		else
		{

		}
	}
}