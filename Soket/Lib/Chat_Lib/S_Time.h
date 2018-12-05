#pragma once
#include "S_Std.h"
class S_Time
{
public:
	TCHAR	 m_csBuffer[256];
	int		 m_iFPS;
	float	 m_fSecondperFrame;
	float	 m_fAccumulation;
public:
	DWORD m_dwBeforeTick;
	float m_fFrameTime;
	DWORD m_dwFrameCnt;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	S_Time();
	virtual ~S_Time();
};

