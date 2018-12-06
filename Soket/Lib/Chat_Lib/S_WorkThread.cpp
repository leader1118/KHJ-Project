#include "S_WorkThread.h"
#include "S_IOCP.h"
#include "S_SvrUser.h"

bool S_WorkThread::Run()
{
	DWORD dwTransfer;
	ULONG_PTR keyValue;
	LPOVERLAPPED LPOV;
	BOOL Return;

	while (1)
	{
		Return = ::GetQueuedCompletionStatus(S_iocp.m_hIOCP, &dwTransfer, &keyValue, &LPOV, INFINITE);
		S_SvrUser* User = (S_SvrUser*)keyValue;
		if (Return == TRUE)
		{
			if (dwTransfer == 0)
			{
				User->
			}
		}


	}
}
void S_WorkThread::Set(HANDLE hIOCP)
{
	m_hIOCP = hIOCP;
}

S_WorkThread::S_WorkThread()
{
}


S_WorkThread::~S_WorkThread()
{
}
