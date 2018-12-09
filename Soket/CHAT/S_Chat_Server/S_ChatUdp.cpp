#include "S_ChatUdp.h"
#include "S_DebugString.h"

bool S_ChatUdp::Init()
{
	m_SendSocket = socket(AF_INET, SOCK_DGRAM, 0);
	m_Socket = socket(AF_INET, SOCK_DGRAM,0);

	int optval = 1;
	setsockopt(m_SendSocket, SOL_SOCKET,
		SO_REUSEADDR, (char*)&optval,
		sizeof(optval));
	setsockopt(m_Socket, SOL_SOCKET,
		SO_REUSEADDR, (char*)&optval,
		sizeof(optval));

	m_RecvAddr.sin_family = AF_INET;
	m_RecvAddr.sin_port = htons(10001);
	m_RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int  retval = ::bind(m_Socket, (SOCKADDR*)&m_RecvAddr, sizeof(m_RecvAddr));
	if (retval == SOCKET_ERROR)return false;

	m_SendAddr.sin_family = AF_INET;
	m_SendAddr.sin_port = htons(9001);
	m_SendAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	CreateThread();

	return true;
}

bool S_ChatUdp::Run()
{
	int retval, addrlen;
	SOCKADDR_IN PeerAddr;
	char buffer[2048] = { 0, };
	while (1)
	{
		addrlen = sizeof(PeerAddr);
		retval = recvfrom(m_Socket, buffer, 2048, 0, (SOCKADDR*)&PeerAddr, &addrlen);
		if (retval == SOCKET_ERROR)
		{
			S_Debug.Print("%s", "ERROR!!!");
			break;
		}

		S_Debug.Print("Recv...IP=%s,PORT=%d,%s",
			inet_ntoa(PeerAddr.sin_addr),
			ntohs(PeerAddr.sin_port), buffer);

		buffer[retval] = 0;
		retval = sendto(m_SendSocket, buffer, strlen(buffer), 0,
			(SOCKADDR*)&m_SendAddr, sizeof(m_SendAddr));

		if (retval == SOCKET_ERROR)
		{
			S_Debug.S_Error(true);
			S_Debug.Print("%s", "Error!!");
			break;
		}
		S_Debug.Print("Send...IP=%s,PORT=%d,%s",
			inet_ntoa(PeerAddr.sin_addr),
			ntohs(PeerAddr.sin_port), buffer);
	}
	closesocket(m_Socket);
	m_Socket = 0;
	return true;
}

bool S_ChatUdp::Release()
{
	if (m_Socket != 0)
	{
		closesocket(m_Socket);
		m_Socket = 0;
	}
	return true;
}

S_ChatUdp::S_ChatUdp()
{
	m_Socket = 0;
}


S_ChatUdp::~S_ChatUdp()
{
}
