#include "S_Thread.h"

unsigned int WINAPI S_Thread::HandleRunner(LPVOID parameter)
{
	S_Thread* pThread = (S_Thread*)parameter;
	if (pThread)
	{
		pThread->Run();
	}
	return 0;
}

void S_Thread::CreateThread()
{
	if (m_bStarted)
	{
		return;
	}
	m_hThread = _beginthreadex(NULL, 0, HandleRunner, (LPVOID)this, 0, &m_iThreadID);
	m_bStarted = true;
}

bool S_Thread::Run()
{
	return true;
}
S_Thread::S_Thread()
{
	m_bStarted = false;
}


S_Thread::~S_Thread()
{
	Closehandle((HANDLE)m_hThread);
}
