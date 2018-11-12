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
	m_hThread = _beginthreadex( // 루틴을 시작하는 함수를 만든다.
		NULL,
		0,
		HandleRunner, //  시작함수
		(LPVOID)this, //  인자값
		0,
		&m_iThreadID);

	// _beginthreadex 인자값
	/*_In_opt_  void*                    _Security,
		_In_      unsigned                 _StackSize,
		_In_      _beginthreadex_proc_type _StartAddress,
		_In_opt_  void*                    _ArgList,
		_In_      unsigned                 _InitFlag,
		_Out_opt_ unsigned*                _ThrdAddr*/
}

SThread::SThread()
{
	m_bStarted = false; // 기본을 false로 준다
}


SThread::~SThread()
{
	CloseHandle((HANDLE)m_hThread); // 쓰레드를 닫는다.
}
