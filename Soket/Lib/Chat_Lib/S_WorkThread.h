#pragma once
#include "S_Thread.h"
class S_WorkThread : public S_Thread
{
public:
	HANDLE m_hIOCP;
public:
	bool Run();
	void Set(HANDLE hIOCP);
public:
	S_WorkThread();
	virtual ~S_WorkThread();
};

