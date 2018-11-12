#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			MessageBox(NULL,L"윈도우가 떳다",L"윈도우가 떳다",MB_OK);
		}
	case WM_LBUTTONDOWN:
	{
		DestroyWindow(hWnd);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0); // WM_QUIT-->> Push
		//DestroyWindow(hWnd); //WM_DESTROY---> PUSH
	}return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
void  GameRun()
{
	//지형 , 오브젝트 ,이펙트,UI
}
void GameInit()
{
	//지형 , 오브젝트 ,이펙트,UI
}
void GameRelease()
{
	//지형 , 오브젝트 ,이펙트,UI
}
int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevinst,
	LPSTR    IpCmdLine,
	int       nCmdShow)
{
	// 원도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = L"MY Windeow";
	wc.hIcon = LoadIcon(hInst, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDC_IBEAM);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbClsExtra = 0;//클래스의 여분 메모리
	wc.cbWndExtra = 0;//윈도위의 여분 메모리

	if (RegisterClassEx(&wc) == FALSE)
	{
		return 1;
	}
	//윈도우 생성 (등록된 클래스를 사용해서 윈도우생성) // 기본 
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


	//GETMESSAGE
	// 메세지 큐에서 메세지 1개 이상 있을 경우에 1개를 가져옴.

	//WM_QUIT //GETMESSAGE는 게임에서 전혀 필요없는 함수임


	//PeekMessage
	//메세지 큐에서 메세지 있던 없던 없으면 false를 반환.
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