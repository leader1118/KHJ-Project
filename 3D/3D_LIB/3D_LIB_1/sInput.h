#pragma once
#include "Sstd.h"
#include "dinput.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
class sInput : public SSingleton<sInput>
{
private:
	friend class SSingleton<sInput>;
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
	sInput();
public:
	virtual ~sInput();
};
#define I_Input sInput::GetInstance()

