#include "SServerIOCP.h"

bool SServerIOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE,
		0, 0, WORKDER_THREAD_COUNT);
	for (int iThread = 0; iThread < WORKDER_THREAD_COUNT; iThread++)
	{
		m_WorkerThread[iThread].CreateThread();
	}
	return true;
}
bool SServerIOCP::Release()
{
	return true;
}
void SServerIOCP::AddHandleToIOCP(HANDLE hClientSocket, ULONG_PTR dwReturnKey)
{
	::CreateIoCompletionPort(hClientSocket, m_hIOCP, dwReturnKey, 0);
	return;
}

SServerIOCP::SServerIOCP(void)
{
}


SServerIOCP::~SServerIOCP(void)
{
}
