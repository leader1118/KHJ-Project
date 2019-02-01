#pragma once
#include "xStd.h"
#include "dinput.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define KEYSTATECOUNT 256

enum Key_State {
	KEY_FREE = 0,
	KEY_UP = 1,
	KEY_PUSH = 2,
	KEY_HOLD = 3,
};

class xInput : public SSingleton < xInput >
{
private:
	friend class SSingleton<xInput>;
public:
	LPDIRECTINPUT8  m_pDI;
	LPDIRECTINPUTDEVICE8  m_pKey;
	LPDIRECTINPUTDEVICE8  m_pMouse;
	HWND			m_hWnd;

	BYTE			m_KeyState[256];
	DIMOUSESTATE	m_MouseState;
public:
	bool	Init();
	bool	Frame();
	bool	Release();
protected:
	xInput();
public:
	virtual ~xInput();
};

#define I_Input xInput::GetInstance()
