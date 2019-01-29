#pragma once
#include "xStd.h"
/*
 1) 1프레임의 경과 시간=m_fSecPerFrame
 2) 1초의 프레임 카운터
 3) 게임이 실행된 누적시간
*/
class xTimer
{
public:
	LARGE_INTEGER m_Frequency;
	DWORD m_dwFrameCount;
	DWORD m_dwFPS;
	LARGE_INTEGER m_dwBeforeTick;
	LARGE_INTEGER m_Elapse;
	LARGE_INTEGER m_Start;
	float m_fSecPerFrame;
	float m_fGameTimer;
	float m_fTimer;
	TCHAR m_csBuffer[256];
	bool m_bStarted;
	float m_fEventTime;

public:
	bool	Init();		// 초기화
	bool	Frame();	// 계산
	bool	Render();	// 드로우
	bool	Release();	// 소멸, 삭제
	float	GetElapsedTime();
public:
	xTimer();
	virtual ~xTimer();
};

class CStopwatch
{
public:
	CStopwatch() { QueryPerformanceFrequency(&m_liPerFreq); Start(); }
	void Start() { QueryPerformanceCounter(&m_liPerfStart); }

	__int64 Now()
	{    // Start 가 호출된 후 경과한 밀리초를 리턴
		LARGE_INTEGER liPerfNow;
		QueryPerformanceCounter(&liPerfNow);
		__int64 qwElapsedTime = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart)));// / m_liPerFreq.QuadPart);
		return qwElapsedTime;
	}
	void Output(const TCHAR* pData)
	{
#ifdef _DEBUG
		TCHAR  strMessage[MAX_PATH] = { 0, };
		__int64 qwElapsedTime = Now();
		//float Second = static_cast<float>(qwElapsedTime) / static_cast<float>(m_liPerFreq.QuadPart);
		_stprintf_s(strMessage, _T("<=====%s[%lld]====>"), pData, qwElapsedTime);
		OutputDebugString(strMessage);
#endif
	}
private:
	LARGE_INTEGER m_liPerFreq;    // 초당 계수
	LARGE_INTEGER m_liPerfStart;   // 시작 계수
};