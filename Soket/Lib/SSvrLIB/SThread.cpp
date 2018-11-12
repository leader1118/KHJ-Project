#include "SThread.h"

unsigned int WINAPI SThread::HandleRunner(LPVOID parameter)
{
	SThread* pThread = (SThread*)parameter;
	if (pThread) pThread->Run();
	return 0;
}
bool SThread::Run()
{
	return true;
}
void SThread::CreateThread()
{
	if (m_bStarted == true)return;
	m_hThread = _beginthreadex( // ��ƾ�� �����ϴ� �Լ��� �����.
		NULL,
		0,
		HandleRunner, //  �����Լ�
		(LPVOID)this, //  ���ڰ�
		0,
		&m_iThreadID);

	// _beginthreadex ���ڰ�
	/*_In_opt_  void*                    _Security,
		_In_      unsigned                 _StackSize,
		_In_      _beginthreadex_proc_type _StartAddress,
		_In_opt_  void*                    _ArgList,
		_In_      unsigned                 _InitFlag,
		_Out_opt_ unsigned*                _ThrdAddr*/
}

SThread::SThread()
{
	m_bStarted = false; // �⺻�� false�� �ش�
}


SThread::~SThread()
{
	CloseHandle((HANDLE)m_hThread); // �����带 �ݴ´�.
}
