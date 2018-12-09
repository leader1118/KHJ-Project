#pragma once
#include "S_Thread.h"
class S_ChatUdp: public S_Thread
{
public:
	SOCKET m_Socket;
	SOCKET m_SendSocket;
	SOCKADDR_IN m_RecvAddr;
	SOCKADDR_IN m_SendAddr;
public:
	bool Init();
	bool Run();
	bool Release();
public:
	S_ChatUdp();
	virtual ~S_ChatUdp();
};

