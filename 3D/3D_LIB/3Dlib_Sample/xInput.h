#pragma once
#include "xStd.h"
#include "dinput.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class xInput : public TSingleton < xInput >
{
private:
	friend class TSingleton<xInput>;
public:
	LPDIRECTINPUT8  m_pDI;
	LPDIRECTINPUTDEVICE8  m_pKey;
	LPDIRECTINPUTDEVICE8  m_pMouse;

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
