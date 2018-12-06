#include "S_IOCP.h"

bool S_IOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 3);

	for (int Thread = 0; Thread < 3; Thread++)
	{
		m_WorkThread[Thread].CreateThread();
	}
	return true;
}
bool S_IOCP::Run()
{
	return true;
}
bool S_IOCP::Release()
{
	return true;
}
void S_IOCP::AddhandleToIOCP(HANDLE hClientSocket, ULONG_PTR dwReturnkey)
{
	::CreateIoCompletionPort(hClientSocket, m_hIOCP, dwReturnkey, 0);
	return;
}
S_IOCP::S_IOCP()
{
}


S_IOCP::~S_IOCP()
{
}
