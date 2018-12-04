#pragma once
#include "SThread.h"
#include <WS2tcpip.h>

class SUdpSocket : public SThread
{
public:
	SOCKET		m_Socket;
	SOCKET		m_RecvSocket;
	SOCKADDR_IN	m_RecvAddr;
	SOCKADDR_IN m_SendAddr;
	vector<string>m_ipList;
public:
	bool	Init();
	bool	Run();
	bool	Release();
	int		GetIPList();
public:
	SUdpSocket(void);
	virtual ~SUdpSocket(void);
};

