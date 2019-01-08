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
	bool	Init();		// �ʱ�ȭ
	bool	Frame();	// ���
	bool	Render();	// ��ο�
	bool	Release();	// �Ҹ�, ����
public:
	sTimer();
	virtual ~sTimer();
};

