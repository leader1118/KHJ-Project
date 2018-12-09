#include "S_UdpSocket.h"
#include "S_DebugString.h"

int S_UdpSocket::GetIPList()
{
	char szHostName[1024] = { 0, };
	int iValue = ::gethostname(szHostName, 1024);
	if (iValue == 0)
	{
		for (int s = 0; s < 255; s++)
		{
			struct hostent* pHost;
			pHost = gethostbyname(szHostName);
			if (pHost != NULL)
			{
				if (pHost->h_addr_list[s])
				{
					BYTE IP[4];
					char iplist[256] = { 0, };
					IP[0] = (BYTE)pHost->h_addr_list[s][0];
					IP[1] = (BYTE)pHost->h_addr_list[s][1];
					IP[2] = (BYTE)pHost->h_addr_list[s][2];
					IP[3] = (BYTE)pHost->h_addr_list[s][3];
					sprintf_s(iplist, "%d.%d.%d.%d",
						IP[0], IP[1], IP[2], IP[3]);
					m_ipList.push_back(iplist);
				}
				else
				{
					break;
				}
			}
		}
	}
	return m_ipList.size();
}

bool S_UdpSocket::Init()
{
	GetIPList();
	m_RecvSocket = socket(AF_INET, SOCK_DGRAM, 0);
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

	int optval = 1;
	setsockopt(m_RecvSocket, SOL_SOCKET,
		SO_REUSEADDR, (char*)&optval,
		sizeof(optval));
	setsockopt(m_Socket, SOL_SOCKET,
		SO_REUSEADDR, (char*)&optval,
		sizeof(optval));

	m_RecvAddr.sin_family = AF_INET;
	m_RecvAddr.sin_port = htons(9001);
	m_RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int retval = ::bind(m_RecvSocket, (SOCKADDR*)&m_RecvAddr, sizeof(m_RecvAddr));

	if (retval == SOCKET_ERROR)
	{
		S_Debug.Print("%s", "ERROR!!!!");
		return false;
	}
	m_SendAddr.sin_family = AF_INET;
	m_SendAddr.sin_port = htons(10001);
	m_SendAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	CreateThread();
	return true;
}

bool S_UdpSocket::Run()
{
	int retval;
	int addrlen;
	SOCKADDR_IN PeerAddr;
	char buf[2048] = "접속 완료";
	while (1)
	{
		retval = sendto(m_Socket, buf, strlen(buf), 0,
			(SOCKADDR*)&m_SendAddr, sizeof(m_SendAddr));
		if (retval == SOCKET_ERROR)break;

		ZeroMemory(buf, sizeof(char) * 2048);
		addrlen = sizeof(PeerAddr);
		retval = recvfrom(m_RecvSocket, buf, 2048, 0,
			(SOCKADDR*)&PeerAddr, &addrlen);
		if (retval == SOCKET_ERROR)break;
		buf[retval] = 0;
		S_Debug.Print("Recv,,,IP = %s, PORT = %d, %s",
			inet_ntoa(PeerAddr.sin_addr), ntohs(PeerAddr.sin_port), buf);

		Sleep(1000);
	}
	closesocket(m_Socket);
	m_Socket = 0;
	return true;
}

bool S_UdpSocket::Release()
{
	if (m_Socket != 0)
	{
		closesocket(m_Socket);
		m_Socket = 0;
	}
	return true;
}


S_UdpSocket::S_UdpSocket()
{
	m_Socket = 0;
}


S_UdpSocket::~S_UdpSocket()
{
}
