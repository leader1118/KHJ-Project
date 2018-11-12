#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM iParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(NULL, L"�����찡 ����", L"�����찡 ����", MB_OK);
	}
	case WM_LBUTTONDOWN:
	{
		DestroyWindow(hWnd);

	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, iParam);
}

void  GameRun()
{
	//���� , ������Ʈ ,����Ʈ,UI
}
void GameInit()
{
	//���� , ������Ʈ ,����Ʈ,UI
}
void GameRelease()
{
	//���� , ������Ʈ ,����Ʈ,UI
}

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevinst,
	LPSTR IpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = L"MY WINDOW";
	wc.hIcon = LoadIcon(hInst, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDC_IBEAM);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (RegisterClassEx(&wc) == FALSE)
	{
		return 1;
	}

	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"MY Windeow", L"KGCA SAMPLES",
		WS_OVERLAPPEDWINDOW,
		0, 0, 800, 600,
		NULL, NULL,
		hInst, NULL);
	if (hWnd == NULL)
	{
		return 1;
	}
	ShowWindow(hWnd, SW_SHOW);


	GameInit();
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
		}
		else
		{
			//ȭ�鿡 ���𰡸� �Ѹ���.(DRAW);
			GameRun();
		}
	}
	GameRelease();
	return 0;
}