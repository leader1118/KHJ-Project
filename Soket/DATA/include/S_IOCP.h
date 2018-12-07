#pragma once
#include "S_WorkThread.h"
#include "S_SvrUser.h"

class S_IOCP : public S_SvrObj,public Singleton<S_IOCP>
{
private:
	friend class Singleton<S_IOCP>;
public:
	HANDLE m_hIOCP;
	S_WorkThread m_WorkThread[3];
public:
	bool Init();
	bool Run();
	bool Release();
	void AddhandleToIOCP(HANDLE hClientSocket, ULONG_PTR dwReturnkey);
public:
	S_IOCP();
	virtual ~S_IOCP();
};
#define S_iocp S_IOCP::GetInstance()

