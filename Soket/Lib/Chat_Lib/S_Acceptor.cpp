#include "S_Acceptor.h"
#include "S_DebugString.h"


bool S_Acceptor::Run()
{
	SOCKET		m_ClientSocket;
	SOCKADDR_IN m_ClientAddr;
	int			m_iAddrlen;

	while (m_bStarted)
	{
		m_iAddrlen = sizeof(m_ClientAddr);
		m_ClientSocket = accept(m_ListenSock, (SOCKADDR*)&m_ClientAddr, &m_iAddrlen);

		if (m_ClientSocket == INVALID_SOCKET)
		{
			continue;
		}

		Adduser(m_ClientSocket, m_ClientAddr);
		Sleep(10);
	}
	return true;
}
bool S_Acceptor::Release()
{
	return true;
}
bool S_Acceptor::Set(int iPort, const char* strAddress)
{
	int Ret;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSock == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN SvrAddr;
	ZeroMemory(&SvrAddr, sizeof(SvrAddr));
	SvrAddr.sin_family = AF_INET;
	if (strAddress == NULL)
	{
		SvrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		SvrAddr.sin_addr.s_addr = inet_addr(strAddress);
	}

	SvrAddr.sin_port = htons(iPort);
	Ret = ::bind(m_ListenSock, (SOCKADDR*)&SvrAddr, sizeof(SvrAddr));
	if (Ret == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
		case WSAEADDRINUSE:
		case WSAEACCES:
			S_Debug.S_Error();
			break;
		}
		return false;
	}

	Ret = listen(m_ListenSock, SOMAXCONN);
	if (Ret == SOCKET_ERROR)
	{
		return false;
	}

	char Flag = 1;
	if (SOCKET_ERROR == setsockopt(m_ListenSock, IPPROTO_TCP, TCP_NODELAY, &Flag, sizeof(char)))
	{
	return false;
	}

	int optvalexe = 1;
	Ret = setsockopt(m_ListenSock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&optvalexe, sizeof(optvalexe));
	if (Ret == SOCKET_ERROR)
	{
		S_Debug.S_Error();
	}

	linger optval2;
	int Size = sizeof(optval2);
	optval2.l_linger = 1000;
	optval2.l_onoff = 1;
	getsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&optval2, &Size);

	setsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&optval2, Size);

	int socketType1;
	int typeLen1 = sizeof(socketType1);
	getsockopt(m_ListenSock, SOL_SOCKET, SO_TYPE, (char*)&socketType1, &typeLen1);

	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType1, &typeLen1) < 0)
	{
		S_Debug.S_Error();
	}
	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType1, &typeLen1) < 0)
	{
		S_Debug.S_Error();
	}

	int SandBufferSize = 10000;
	int SandBufferSizelen = sizeof(SandBufferSizelen);
	if (setsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&SandBufferSize, SandBufferSizelen) < 0)
	{
		S_Debug.S_Error();
	}

	int rcvBufferSizeLen = sizeof(int);
	int rcvBufferSize = 10000;
	if (setsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufferSize, rcvBufferSizeLen) < 0)
	{
		S_Debug.S_Error();
	}

	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType1,
		&typeLen1) == SOCKET_ERROR)
	{
		S_Debug.S_Error();
	}
	if (getsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType1,
		&typeLen1) == SOCKET_ERROR)
	{
		S_Debug.S_Error();
	}

	CreateThread();
	return true;
}

void S_Acceptor::Adduser(SOCKET socket, SOCKADDR_IN address)
{
	char buf[MAX_ARRAY] = { 0, };
	InetNtopA(AF_INET, &address.sin_addr, buf, sizeof(char)*MAX_ARRAY);
}

S_Acceptor::S_Acceptor()
{
}


S_Acceptor::~S_Acceptor()
{
}
