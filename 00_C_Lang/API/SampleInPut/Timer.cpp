#include "Timer.h"

bool	Timer::Init()
{
	//__imp_timeGetTime 외부 기호 : winmm.lib
	m_dwBeforeTick = timeGetTime(); // 1/1000
	return true;
}
bool	Timer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	m_fSecPerFrame = dwElapseTick / 1000.0f;
	m_fGameTimer += m_fSecPerFrame;

	m_fTimer += m_fSecPerFrame;
	if (m_fTimer >= 1.0f)
	{
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fTimer -= 1.0f;
		_stprintf_s(m_csBuffer,
			L"FPS:%d TIME:%10.4f SPF:%10.4f",
			m_dwFPS, m_fGameTimer, m_fSecPerFrame);
		//OutputDebugString(m_csBuffer);
	}
	m_dwFrameCount++;

	m_dwBeforeTick = dwCurrentTick;
	return true;
}
bool	Timer::Render()
{
	HDC hdc = GetDC(g_hWnd);
	SetBkColor(hdc, RGB(255, 0, 0));
	SetTextColor(hdc, RGB(0, 0, 255));
	//SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 0, 0, m_csBuffer, wcslen(m_csBuffer));
	ReleaseDC(g_hWnd, hdc);
	return true;
}
bool	Timer::Release()
{
	return true;
}

Timer::Timer()
{
	m_fGameTimer = 0.0f;
	m_dwFrameCount = 0;
	m_dwFPS = 0;
	m_dwBeforeTick = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
	m_fTimer = 0.0f;
}


Timer::~Timer()
{
}
