#include "S_Main.h"
#include "S_DebugString.h"
#include "S_Input.h"

LRESULT S_Main::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		m_hEdit = CreateWindow(_T("edit"),
			NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			500, 10, 200, 25, hWnd,
			(HMENU)202, m_hInstance, NULL);
		CreateWindow(_T("button"), _T("Send"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			700, 10, 50, 25, hWnd,
			(HMENU)302, m_hInstance, NULL);

		int iWidth = 800;
		int iHeight = 600;
		S_Debug.m_hList = CreateWindow(L"listbox", NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL,
			0, 0, iWidth - 300, iHeight,
			hWnd, (HMENU)0, m_hInstance, NULL);
	}return 0;
	case WM_COMMAND:
	
		switch (LOWORD(wParam))
		{
		case 302:
		{
			GetWindowText(m_hEdit, m_strBuf, 128);
			S_Debug.ConvertWideStringToAnsiCch(m_Client.m_strBuf, m_strBuf, 128);
			InvalidateRect(hWnd, NULL, NULL);
			if (m_Client.m_LoginOk == false && m_Client.SendMsg(m_Client.m_strBuf, PACKET_CHAT_NAME_ACK))
			{
				m_Client.m_LoginOk = true;
			}
			else
			{
				m_Client.m_Send = true;
			}
		}
		}
		break;
	case WM_CHAR:
		break;
	}
	return -1;
}

bool S_Main::Init()
{
	m_Client.Init();
	m_UDP.Init();
	return true;
}

bool S_Main::Frame()
{
	if (S_INPUT.StayKeydown(VK_LEFT))
	{
		SPACKET_USER_POSITION UserData;
		UserData.direction = VK_LEFT;
		UserData.PosX = 100;
		UserData.PosY = 100;
		UserData.user_idx = 999;
		char buffer[256] = { 0, };
		int Size = sizeof(UserData);
		memcpy(buffer, &UserData, Size);
		m_Client.SendMsg(buffer, Size, PACKET_USER_POSITION);
	}
	m_Client.ProcessPacket();
	m_Client.Frame();
	return true;
}
bool S_Main::Release()
{
	m_UDP.Release();
	m_Client.Release();
	return true;
}

S_Main::S_Main()
{
}


S_Main::~S_Main()
{
}

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPWSTR strCmdLine, INT nShow)
{
	S_Main Client;
	if (!Client.SetWindow(hInst, _T("S_Chat_Client"), 800, 600))
	{
		return 0;
	}
	SetCursor(NULL);

	if (Client.Run() == false)
	{
		return 0;
	}
	return 1;
}