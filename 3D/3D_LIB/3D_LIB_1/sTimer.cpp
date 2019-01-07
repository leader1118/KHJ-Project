#include "sTimer.h"


float g_fSecPerFrame = 0.0f;
float g_fGameTimer = 0.0f;

bool	sTimer::Init()
{
	QueryPerformanceCounter(&m_dwBeforeTick);
	return true;
}
bool	sTimer::Frame()
{
	LARGE_INTEGER dwCurrentTick;
	QueryPerformanceCounter(&dwCurrentTick);
	LONGLONG dwElapseTick =
		(dwCurrentTick.QuadPart -
			m_dwBeforeTick.QuadPart);
	m_fSecPerFrame = (float)dwElapseTick / m_Frequency.QuadPart;
	g_fSecPerFrame = m_fSecPerFrame;
	m_fGameTimer += m_fSecPerFrame;

	g_fSecPerFrame = m_fSecPerFrame;
	g_fGameTimer = m_fGameTimer;

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
bool	sTimer::Render()
{
	return true;
}
bool	sTimer::Release()
{
	return true;
}
sTimer::sTimer()
{
	m_fGameTimer = 0.0f;
	m_dwFrameCount = 0;
	m_dwFPS = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
	m_fTimer = 0.0f;
	QueryPerformanceFrequency(&m_Frequency);
}


sTimer::~sTimer()
{
}
