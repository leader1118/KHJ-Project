#include "CCCore.h"

bool	CCCore::GameInit()
{
	m_Timer.Init();
	m_Input.Init();
	// 제 1의 버퍼 전면버퍼
	m_hScreenDC = GetDC(m_hWnd);
	// 제 2의 버퍼를 생성한다.
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC); //메모리
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC,
		m_rtClient.right,
		m_rtClient.bottom);
	// 반환값 = 이전 선택되어 있던 비트맵
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);
	
	Init();
	return true;
}

bool	CCCore::GameRelease()
{
	Release();
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	ReleaseDC(m_hWnd, m_hScreenDC);
	m_Timer.Release();
	m_Input.Release();
	return true;
}
bool	CCCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	Frame();

	return true;
}
bool CCCore::PreRender()
{
	// m_hOffScreenDC를 지운다.
	COLORREF bkColor = RGB(255, 255, 255);
	HBRUSH hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, hbrBack);
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtClient.right, m_rtClient.bottom,
		PATCOPY);
	return true;
}

bool CCCore::PostRender()
{
	// m_hOffScreenDC 이미지를 m_hScreenDC로 복사해라.
	BitBlt(m_hScreenDC, m_rtClient.left, m_rtClient.top,
		m_rtClient.right, m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool	CCCore::DrawDebug()
{
	RECT rect;
	if (m_hOffScreenDC != NULL)
	{
		GetClientRect(m_hWnd, &rect);
		SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetTextColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		// 그리기
		DrawText(m_hOffScreenDC, m_Timer.m_csBuffer, -1,
			&rect, DT_LEFT | DT_VCENTER);
		//SetTextAlign(hdc,TA_LEFT);
		//TextOut(hdc,100,100,L"KHJ",
		//wcslen(L"KHJ"));
	}
	return true;
}
bool	CCCore::GameRender()
{
	PreRender();
	Render();
	m_Timer.Render();
	m_Input.Render();
	DrawDebug();
	PostRender();
	return true;
}
bool CCCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
void CCCore::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
}
CCCore::CCCore()
{
}


CCCore::~CCCore()
{
}
