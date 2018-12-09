#pragma once
#include "S_Thread.h"

class S_UdpSocket : public S_Thread
{
public:
	SOCKET			m_Socket;
	SOCKET			m_RecvSocket;
	SOCKADDR_IN		m_RecvAddr;
	SOCKADDR_IN		m_SendAddr;
	vector<string>  m_ipList;
public:
	bool	Init();
	bool	Run();
	bool	Release();
	int		GetIPList();
public:
	S_UdpSocket();
	virtual ~S_UdpSocket();
};

