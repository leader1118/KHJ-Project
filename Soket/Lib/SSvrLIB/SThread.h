#pragma once
#include "SServerObj.h"
class SThread : public SServerObj
{
public:
	unsigned int	m_hThread; // 쓰레드 변수
	unsigned int	m_iThreadID; // 쓰레드 ID 변수
	bool			m_bStarted; // 쓰레드의 시작지점 변수
public:
	void			CreateThread(); // 쓰레드 생성 함수
	virtual bool	Run(); // 돌리는 함수
	static unsigned int WINAPI HandleRunner(LPVOID parameter); // 쓰레드를 돌리는 함수
public:
	SThread(void);
	virtual ~SThread(void);
};

