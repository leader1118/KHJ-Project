#include "CCSample.h"

//// 클래스 멤버 변수 초기화
bool			CCSample::Init()
{
	TCHAR	str[] = _T("NAME");
	TCHAR	str2[] = _T("NAME");
	_tcscpy(str, str2);
	return true;
}
//// 매 프레임에서 계산을 담당한다.
bool		CCSample::Frame()
{
	if (m_Input.KeyCheck(VK_LEFT) == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"VK_LEFT", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck(VK_RIGHT) == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"VKRIGHT", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck(VK_UP) == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"VK_UP", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck(VK_DOWN) == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"VK_DOWN", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck('0') == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"0", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck('A') == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"A", L"KEY", MB_OK);
	}
	if (m_Input.KeyCheck(VK_F1) == KEY_PUSH)
	{
		MessageBox(g_hWnd, L"VK_F1", L"Key", MB_OK);
	}
	return true;
}

// 매 프레임에서 드로우를 담당한다.
bool	CCSample::Render()
{
	RECT rect;
	if (m_hOffScreenDC != NULL)
	{
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		for (int iCnt = 0; iCnt < m_Input.m_strList.size();
			iCnt++)
		{
			//SetTextAlign(hdc,TA_LEFT);
			TextOut(m_hOffScreenDC,
				0, 100 + iCnt * 20,
				m_Input.m_strList[iCnt].c_str(),
				m_Input.m_strList[iCnt].size());
		}
	}
	return true;
}
//// 클래스 멤버 변수 소멸을 담당한다.
// bool		CCSample :: Release()
//{
//	return true;
//};

CCSample::CCSample()
{
}


CCSample::~CCSample()
{
}

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR	IpCmdLine,
	int		nCmdShow)
{
	CCSample sample;
	// 윈도우를 생성한다.
	if (sample.SetWindow(hInstance,0, 800, 600))
	{
		// 생성된 윈도우를 가동한다.
		sample.Run();
	}
}
