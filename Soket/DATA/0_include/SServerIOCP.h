#pragma once
#include "SWorkThread.h"
#include "SUser.h"
#include "SSingleton.h"

#define WORKDER_THREAD_COUNT 3
class SServerIOCP : public SSingleton<SServerIOCP>, public SServerObj
{
private:
	friend class SSingleton<SServerIOCP>;
public:
	HANDLE				m_hIOCP;
	SWorkThread			m_WorkerThread[WORKDER_THREAD_COUNT];
public:
	bool		Init();
	bool		Release();
	void		AddHandleToIOCP(HANDLE hClientSocket, ULONG_PTR dwReturnKey);
public:
	SServerIOCP(void);
	virtual ~SServerIOCP(void);
};
#define I_ServerIOCP SServerIOCP::GetInstance()
