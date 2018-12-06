#pragma once

#include "S_Thread.h"

class S_Acceptor : public S_Thread
{
public:
	SOCKET m_ListenSock;
public:
	bool Run();
	bool Release();
	bool Set(int iPort, const char* strAddress = 0);
	virtual void Adduser(SOCKET socket, SOCKADDR_IN address);
public:
	S_Acceptor();
	virtual ~S_Acceptor();
};

