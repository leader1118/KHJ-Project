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
				User->DeleteUser();
			}
			if (dwTransfer != 0 && LPOV != 0)
			{
				User->Dispatch(dwTransfer, LPOV);
			}
			else
			{
				if (GetLastError() != ERROR_OPERATION_ABORTED)
				{
					if (dwTransfer == 0)
					{
						User->DeleteUser(User->m_Socket);
					}
				}
			}
		}
	}
	return true;
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
