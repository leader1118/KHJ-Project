#pragma once
#include "S_Core.h"
#include "S_ChatUdp.h"
class S_ChatMain : public S_Core
{
public:
	S_ChatUdp m_UDP;
public:
	bool Init();
	bool Release();
	bool PreRender() { return true; }
	bool PostRender() { return true; }
public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	S_ChatMain();
	virtual ~S_ChatMain();
};

