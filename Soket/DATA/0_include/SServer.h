#pragma once
#include "SThread.h"
#include "SAcceptor.h"
#include "SStreamPacket.h"
#include "SUser.h"
class SServer : public SThread
{
public:
	SAcceptor		m_Acceptor;
public:
	bool			Init();
	bool			Release();
	bool			Run();
	virtual bool	AddUser(SOCKET socket, SOCKADDR_IN address);
	bool			SendMsg(SOCKET socket, char* msg, WORD code);
public:
	SServer(void);
	virtual ~SServer(void);
};

