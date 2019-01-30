#pragma once
#include "xStd.h"
/*
 1) 1�������� ��� �ð�=m_fSecPerFrame
 2) 1���� ������ ī����
 3) ������ ����� �����ð�
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
	bool	Init();		// �ʱ�ȭ
	bool	Frame();	// ���
	bool	Render();	// ��ο�
	bool	Release();	// �Ҹ�, ����
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
	{    // Start �� ȣ��� �� ����� �и��ʸ� ����
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
	LARGE_INTEGER m_liPerFreq;    // �ʴ� ���
	LARGE_INTEGER m_liPerfStart;   // ���� ���
};