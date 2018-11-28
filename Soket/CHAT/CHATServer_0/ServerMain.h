#pragma once
#include "TCore.h"
#include "sUdpSocket.h"
class ServerMain: public TCore
{
public:
	sUdpSocket m_Udp;
public:
	bool Init();
	bool Release();
	bool PreRender() { return true;}
	bool PostRender() { return true; }

public:
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	ServerMain(void);
	virtual ~ServerMain(void);
};

