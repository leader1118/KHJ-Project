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
	xTimer();
	virtual ~xTimer();
};

