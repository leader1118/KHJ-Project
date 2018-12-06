#pragma once
#include "S_Thread.h"
#include "S_Acceptor.h"
#include "S_SvrUser.h"

class S_Server:public S_Thread
{
public:
	S_Acceptor m_Acceptor;
public:
	bool Init();
	bool Release();
	bool Run();
	virtual bool AddUser(SOCKET socket, SOCKADDR_IN address);
	bool SendMsg(SOCKET socket, char* msg, WORD code);
public:
	S_Server();
	virtual ~S_Server();
};

