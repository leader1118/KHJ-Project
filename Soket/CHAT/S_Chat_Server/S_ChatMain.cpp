#include "S_ChatMain.h"
#include "S_Chat_Svr.h"
#include "S_IOCP.h"
#include "S_DebugString.h"

bool S_ChatMain::Init()
{
	S_iocp.Init();
	S_CHAT.Init();
	m_UDP.Init();
	return true;
}

bool S_ChatMain::Release()
{
	m_UDP.Release();
	S_CHAT.Release();
	return true;
}

LRESULT S_ChatMain::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		int iWidth = 800;
		int iHeight = 600;
		S_Debug.m_hList = CreateWindow(L"ListBox", NULL,
			WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
			0, 0, iWidth, iHeight,
			hWnd, (HMENU)0, m_hInstance, NULL);
	}break;
	}
	return 0;
}

S_ChatMain::S_ChatMain()
{
}


S_ChatMain::~S_ChatMain()
{
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	S_ChatMain Main;
	if (!Main.SetWindow(hInstance, _T("chat_Svr"), 800, 600))
	{
		return 0;
	}
	SetCursor(NULL);

	if (Main.Run() == false)
	{
		return 0;
	}
	return 1;
}