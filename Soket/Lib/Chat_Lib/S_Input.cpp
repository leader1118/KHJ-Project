#include "S_Input.h"

bool S_Input::StayKeydown(INT iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		return TRUE;
	}
}

bool S_Input::OnceKeydwon(INT iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		
		if (m_bKeydown[iKey] == false)
		{
			m_bKeydown[iKey] = true;
			return TRUE;
		}
	}
	else
	{
		
		m_bKeydown[iKey] = false;
	}

	return FALSE;
}

bool S_Input::OnceKeyUp(INT iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		m_bKeyUp[iKey] = true;
	}

	else
	{
		
		if (m_bKeyUp[iKey] == true)
		{
			
			m_bKeyUp[iKey] = false;

			return TRUE;
		}
	}

	return FALSE;
}
bool S_Input::Init()
{
	ZeroMemory(m_bKeydown, MAX_ARRAY);
	ZeroMemory(m_bKeyUp, MAX_ARRAY);
	return true;
}
bool S_Input::Frame()
{
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(g_hWnd, &m_ptMousePos);
}
bool S_Input::Render()
{
	return true;
}
bool S_Input::Release()
{
	return true;
}
S_Input::S_Input()
{
}


S_Input::~S_Input()
{
}
