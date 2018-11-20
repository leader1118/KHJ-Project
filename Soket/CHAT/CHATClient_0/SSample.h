#pragma once
#include "SCHAT_Client.h"
#include "SUdpSocket.h"
#include "TCore.h"

class SSample : public TCore
{
public:
	SUdpSocket		m_Udp;
	SCHAT_Client	m_Client;
	HWND			m_hEdit;
	HWND			m_hChatEdit;
	TCHAR			m_strBuffer[128];
public:
	bool		Init();
	bool		Frame();
	bool		Release();
	bool		PreRender() { return true; }
	bool		PostRender() { return true; }
	LRESULT		MsgProc(HWND hwnd,
						UINT msg,
						WPARAM wParam,
						LPARAM lParam);
public:
	SSample(void);
	virtual ~SSample(void);
};

