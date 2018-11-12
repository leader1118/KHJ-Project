#pragma once
#include "SThread.h"
class SWorkThread : public SThread
{
public:
	HANDLE		m_hIOCP;
	bool		Run();
	void		Set(HANDLE hIOCP)
	{
		m_hIOCP = hIOCP;
	};
public:
	SWorkThread(void);
	virtual ~SWorkThread(void);
};

