#include "Core.h"

class Sample : public Core
{
public:
	bool	Init()
	{
		return true;
	}
	bool	Frame()
	{
		if (I_Input.Key(VK_LBUTTON) == KEY_PUSH)
		{
			MessageBox(NULL, L"0", L"VK_LBUTTON", MB_OK);
		}
		SHORT sKey = GetAsyncKeyState(VK_LBUTTON);
		if (sKey & 0x8001)
		{
			MessageBox(NULL, L"1", L"m_dwMouseState", MB_OK);
		}
		DWORD dwState = I_Input.m_dwMouseState[0];
		if (dwState == KEY_PUSH)
		{
			MessageBox(NULL, L"2", L"m_dwMouseState", MB_OK);
		}
		if (I_Input.m_dwMouseState[1] == KEY_PUSH)
		{
			//MessageBox(NULL, L"1", L"m_dwMouseState", MB_OK);
		}
		if (I_Input.m_dwMouseState[2] == KEY_PUSH)
		{
			//MessageBox(NULL, L"2", L"m_dwMouseState", MB_OK);
		}
		if (I_Input.Key(VK_END) == KEY_PUSH)
		{
			//MessageBox(NULL, L"KEY_PUSH", L"KEY", MB_OK);
		}
		if (I_Input.Key(VK_END) == KEY_HOLD)
		{
			//MessageBox(NULL, L"KEY_HOLD", L"KEY", MB_OK);
		}
		if (I_Input.Key(VK_END) == KEY_UP)
		{
			//MessageBox(NULL, L"KEY_UP", L"KEY", MB_OK);
		}
		bool bComboKey = I_Input.Key(VK_LCONTROL) == KEY_HOLD && I_Input.Key('p') == KEY_PUSH;
		if (bComboKey)
		{
			MessageBox(NULL, L"bComboKey+p", L"Mouse+Key", MB_OK);
		}
		return true;
	}
	bool	Render() {
		return true;
	}
	bool	Release() {
		return true;
	}
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SampleInput", 800, 600)