#pragma once
#include "S_Lock.h"

class S_Thread : public S_SvrObj
{
public:
	unsigned int m_hThread;
	unsigned int m_iThreadID;
	bool		 m_bStarted;
public:
	void CreateThread();
	virtual bool Run();
	static unsigned int WINAPI HandleRunner(LPVOID parameter);
public:
	S_Thread();
	virtual ~S_Thread();
};

