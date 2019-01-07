#pragma once
#include "Sstd.h"
class sTimer
{
public:
	LARGE_INTEGER m_Frequency;
	DWORD m_dwFrameCount;
	DWORD m_dwFPS;
	LARGE_INTEGER m_dwBeforeTick;
	float m_fSecPerFrame;
	float m_fGameTimer;
	float m_fTimer;
	TCHAR m_csBuffer[256];
public:
	bool	Init();		// 초기화
	bool	Frame();	// 계산
	bool	Render();	// 드로우
	bool	Release();	// 소멸, 삭제
public:
	sTimer();
	virtual ~sTimer();
};

