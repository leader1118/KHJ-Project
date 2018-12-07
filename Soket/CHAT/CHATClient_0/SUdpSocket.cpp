#include "SUdpSocket.h"
#include "SDebugString.h"

int SUdpSocket::GetIPList()
{
	char szHostName[1024] = { 0, };
	int iValue = ::gethostname(szHostName, 1024);
	if (iValue == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			struct hostent* pHost;
			pHost = gethostbyname(szHostName);
			if (pHost != NULL)
			{
				if (pHost->h_addr_list[i])
				{
					BYTE ip[4];
					char iplist[256] = { 0, };
					ip[0] = (BYTE)pHost->h_addr_list[i][0];
					ip[1] = (BYTE)pHost->h_addr_list[i][1];
					ip[2] = (BYTE)pHost->h_addr_list[i][2];
					ip[3] = (BYTE)pHost->h_addr_list[i][3];

					sprintf_s(iplist, "%d.%d.%d.%d",
						ip[0], ip[1], ip[2], ip[3]);
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

bool SUdpSocket::Init()
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
	int ret = ::bind(m_RecvSocket, (SOCKADDR*)&m_RecvAddr, sizeof(m_RecvAddr));
	if (ret == SOCKET_ERROR)
	{
		I_Debug.Print("[%s]", "ERROR!");
		return false;
	}

	/*BOOL bEnable = TRUE; 
	ret = setsockopt(m_Socket, SOL_SOCKET,
		SO_BROADCAST, (char*)&bEnable, sizeof(bEnable));
	if (ret == SOCKET_ERROR)
	{
		I_Debug.Print("[%s]", "ERROR!");
		return false;
	}*/
	m_SendAddr.sin_family = AF_INET;
	m_SendAddr.sin_port = htons(10001);
	m_SendAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	CreateThread();
	return true;
}

bool SUdpSocket::Run()
{
	int retval, addrlen;
	SOCKADDR_IN PeerAddr;
	char buf[2048] = "���� �Ϸ�!";
	while (1)
	{
		retval = sendto(m_Socket, buf, strlen(buf), 0,
			(SOCKADDR*)&m_SendAddr, sizeof(m_SendAddr));
		if (retval == SOCKET_ERROR)  break;

		ZeroMemory(buf, sizeof(char)*2048);
		addrlen = sizeof(PeerAddr);
		retval = recvfrom(m_RecvSocket, buf, 2048, 0,
			(SOCKADDR*)&PeerAddr, &addrlen);
		if (retval == SOCKET_ERROR)  break;
		buf[retval] = 0;
		//OutputDebugStringA((char*)buf);
		I_Debug.Print("[RECV]IP=%s, PORT=%d, %s",
			inet_ntoa(PeerAddr.sin_addr),
			ntohs(PeerAddr.sin_port), buf);

		Sleep(1000);
	}
	closesocket(m_Socket);
	m_Socket = 0;
	return true;
}
bool SUdpSocket::Release()
{
	if (m_Socket != 0)
	{
		closesocket(m_Socket);
		m_Socket = 0;
	}
	return true;
}

SUdpSocket::SUdpSocket(void)
{
	m_Socket = 0;
}


SUdpSocket::~SUdpSocket(void)
{
}