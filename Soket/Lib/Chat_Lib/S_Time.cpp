#include "S_Time.h"

int		g_iFPS;
float	g_fSecPerFrame;
float	g_fAccumulation;


bool	S_Time::Init()
{
	m_dwBeforeTick = timeGetTime();
	ZeroMemory(m_csBuffer, sizeof(TCHAR)* MAX_PATH);
	return true;
};

bool	S_Time::Frame()
{
	//(winmm.lib) ==> timeGetTime을 사용하기 위해서 포함하는 Lib파일
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;

	g_fSecPerFrame = m_fSecondperFrame = dwElapseTick / 1000.0f;
	g_fAccumulation = m_fAccumulation += m_fSecondperFrame;
	m_fFrameTime += m_fSecondPerFrame;

	if (m_fFrameTime > 1.0f)
	{
		g_iFPS = m_iFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime -= 1.0f;
	}

	m_dwFrameCnt++;
	m_dwBeforeTick = dwCurrentTick;
	return true;
};

bool		S_Time::Render()
{
	_stprintf_s(
		m_csBuffer,
		L"Timer:[%10.4f] FPS:[%d] %10.4f\n",
		m_fAccumulation,
		m_iFPS,
		m_fSecondperFrame);
	return true;
};
bool S_Time::Release()
{
	return true;
}
S_Time::S_Time()
{
	m_iFPS = 0;
	m_dwFrameCnt = 0;
	m_fSecondperFrame = 0.0f;
	m_fAccumulation = 0.0f;
	m_fFrameTime = 0.0f;
}


S_Time::~S_Time()
{
}
