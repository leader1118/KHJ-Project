#include "DTimer.h"

bool DTimer::Init()
{
	QueryPerformanceCounter(&m_Frame); // 고해상도 타이머 

	// 고해상도 타이머 지원여부 판단
	if (m_Frame.QuadPart == 0)
	{
		return false;
	}
	m_FPS = m_Frame;
	m_iFramePerSecond = 0;
	m_iFPSElapse = 0;
	m_fSecPerFrame = 0.0f;

	Start();
	return true;
}
bool DTimer::Frame()
{
	// 1프레임의 시간 체크
	// 현재 시간을 찾느다
	QueryPerformanceCounter(&m_Current);
	m_fSecPerFrame = static_cast<float> (m_Current.QuadPart - m_Frame.QuadPart) / static_cast<float>(m_Frequency.QuadPart);

	// 1초당 프레임 체크
	if (((m_Current.LowPart - m_FPS.LowPart) / m_Frequency.LowPart) > 1)
	{
		m_iFramePerSecond = m_iFPSElapse;
		m_iFPSElapse = 0;
		m_FPS = m_Current;
	}
	m_iFPSElapse++;

	m_Frame = m_Current;

	return true;
}

int DTimer::GetFPS()
{
	return m_iFramePerSecond;
}
float DTimer::GetSPF()
{
	return m_fSecPerFrame;
}
bool DTimer::Render()
{
	return true;
}
bool DTimer::Release()
{
	return true;
}
void DTimer::Reset()
{
	m_bStarted = false;
	m_fEventTime = 0.0f;
	memset(&m_Start, 0, sizeof(LARGE_INTEGER));
	memset(&m_Elapse, 0, sizeof(LARGE_INTEGER));
}

void DTimer::Start()
{
	m_bStarted = true;
	m_fEventTime = 0.0f;
	QueryPerformanceCounter((LARGE_INTEGER*)&m_Start);
}
void DTimer::Stop()
{
	GetElapseTime();
	m_bStarted = false;
}
bool DTimer::IsStarted()const
{
	return m_bStarted;
}
float DTimer::GetElapseTime()
{
	if (m_bStarted)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_Elapse);
		m_fEventTime = static_cast<float>(m_Elapse.LowPart - m_Start.LowPart) / static_cast<float>(m_Frequency.LowPart);

	}
	return m_fEventTime;
}

DTimer::DTimer()
{
	m_bStarted = false;
	m_iFramePerSecond = 0;
	m_iFPSElapse = 0;
	m_fSecPerFrame = 0.0f;
	m_fEventTime = 0.0f;

	// 시스템의 주파수 변동폭을 얻어 온다 . 이는 시간의 표준을 잡기 위해서 사용한다.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequency);
}


DTimer::~DTimer()
{
}
