#pragma once

#include "S_Core.h"
#include "S_Client.h"
#include "S_UdpSocket.h"

class S_Main : public S_Core
{
public:
	S_UdpSocket		m_UDP;
	S_Client		m_Client;
	HWND			m_hEdit;
	HWND			m_hChatEdit;
	TCHAR			m_strBuf[128];
public:
	bool		Init();
	bool		Frame();
	bool		Release();
	bool		PreRender() { return true; }
	bool		PostRender() { return true; }
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	S_Main();
	virtual ~S_Main();
};

