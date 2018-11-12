#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		MessageBox(NULL, L"윈도우가 떳다",L"윈도우가 떳다", MB_OK);
	}
	case WM_LBUTTONDOWN:
	{
		DestroyWindow(hWnd);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0); //WM_Quit-->>Push
		//DestroyWindow(hWnd); //WM_DESTROY--->Push
	}return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void GameRun()
{
	//지형, 오브젝트,이펙트,UI
}
void GameInit()
{
	//지형, 오브젝트,이펙트,UI
}
void GameRelease()
{
	//지형, 오브젝트,이펙트,UI
}
int WINAPI WindMain(HINSTANCE hInst,
	HINSTANCE hPrevinst,
	LPSTR IpCmdLine,
	int nCmadSHow)
{
	//Window class 등록
	WNDCLASSEX wc; //Window CLASS 변수 선언
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // 0으로 초기화
	wc.cbSize = sizeof(WNDCLASSEX); // 사이즈 재정의
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = L"MY Window"; // 윈도우창 이름
	wc.hIcon = LoadIcon(hInst, IDI_QUESTION); // 아이콘 그림
	wc.hCursor = LoadCursor(NULL,IDC_IBEAM); // 마우스 아이콘
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH); // window 색상
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbClsExtra = 0; //클래스의 여분 메모리
	wc.cbWndExtra = 0;// 윈도우위 여분 메모리

	if (RegisterClassEx(&wc) == FALSE)
	{
		return 1;
	}
	//윈도우 생성 (등록된 클래스를 사용해서 윈도우생성) //기본
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"Windeow", L"KHJ SAMPLE",
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
			//화면에 무언가를 뿌린다.(DRAW);
			GameRun();
		}
	}
	GameRelease();
	return 0;
}