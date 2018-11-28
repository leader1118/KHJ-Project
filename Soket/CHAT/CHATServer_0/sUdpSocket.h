#pragma once
#include "SThread.h"

class sUdpSocket : public SThread
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
	sUdpSocket(void);
	virtual ~sUdpSocket(void);
};

