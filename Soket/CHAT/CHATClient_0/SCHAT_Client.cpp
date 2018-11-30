#include "SCHAT_Client.h"
#include "SDebugString.h"
#include "SLock.h"

unsigned __stdcall sendMessage(void * arg)
{
	I_Debug.Print("%s","send 스레드 시작");

	SCHAT_Client* pClient = (SCHAT_Client*)arg;

	while (!pClient->m_bExit)
	{
		if (pClient->m_bLoginOK && pClient->m_bSend)
		{
			if (pClient->SendMsg(pClient->m_strBuffer, PACKET_CHAT_MSG) <= 0)
			{
				break;
			}
			pClient->m_bSend = false;
		}

		if (SwitchToThread() == FALSE)
		{
			Sleep(1);
			// Sleep(0)은 동일한 우선순위 스레드 스위칭 되지만
			// Sleep(1)은 서로 다른 우선순위 스레드에서도 스위칭이 된다.
		}
	}
	return 0;
}
unsigned __stdcall receiveMessage(void* arg)
{
	I_Debug.Print("%s", "receive 스레드 시작");
	
	SCHAT_Client* pClient = (SCHAT_Client*)arg;

	int iSocket = pClient->m_iSocket;
	char strBuffer[2048] = { 0, };

	while (!pClient->m_bExit)
	{
		int iRet = recv(iSocket, strBuffer, sizeof(strBuffer), 0);
		if (iRet <= 0)
		{
			// 비동기 소켓
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}
			pClient->m_bExit = true;
			closesocket(pClient->m_iSocket);
			break;
		}
		strBuffer[iRet] = 0;
		pClient->m_StreamPacket.Put(strBuffer, iRet, pClient);
		// Sleep(1) 또는 SwitchtoThread()를 사용하면 우선순위가 낮은 스레드에도 스위칭이 가능하다.
		if (SwitchToThread() == FALSE)
		{
			Sleep(1);
		}
	}
	return 0;
}

// 완성된 패킷에 대한 처리
int SCHAT_Client::ProcessPacket()
{
	{
		SLock lock(this);
		list<S_PACKET>::iterator	itor;
		for (itor = m_StreamPacket.m_PacketList.begin();
			itor != m_StreamPacket.m_PacketList.end();
			itor++)
		{
			UPACKET* pPacket = &(*itor).packet;
			switch (pPacket->ph.type)
			{
			case PACKET_USER_POSITON:
			{
				SPACKET_USER_POSITON user;
				memcpy(&user, pPacket->msg,
					sizeof(char)* pPacket->ph.len - 4);
				if (user.bDirection == VK_DOWN)
				{
					int kkk = 0;
				}
				if (user.bDirection == VK_LEFT)
				{
					int kkk = 0;
				}
				if (user.bDirection == VK_RIGHT)
				{
					int kkk = 0;
				}
				if (user.bDirection == VK_UP)
				{
					int kkk = 0;
				}
			}break;
			case PACEKT_CHAT_NAME_REQ:
			{
				I_Debug.Print("%s", pPacket->msg);
			}break;
			case PACKET_CHAT_MSG:
			{
				I_Debug.Print("%s", pPacket->msg);
			}break;
			}
		}
		m_StreamPacket.m_PacketList.clear();
	}
	return 1;
}

int SCHAT_Client::SendMsg(char* pMsg, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sprintf_s(sendmsg.msg, pMsg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + strlen(sendmsg.msg);
	
	int iRet = send(m_iSocket, (char*)&sendmsg, sendmsg.ph.len, 0);

	if (iRet <= 0)
	{
		m_bSend = false;
		// 비동기 소켓
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		return 0;
	}
	m_bSend = false;
	return 1;
}

int SCHAT_Client::SendMsg(char*pMsg, int iSize, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	memcpy(sendmsg.msg, pMsg, iSize);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + iSize;

	int iRet = send(m_iSocket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		m_bSend = false;

		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		return 0;
	}
	m_bSend = false;
	return 1;
}

int SCHAT_Client::CreateConnectSocket(int iPort)
{
	int Rv;
	m_iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_iSocket == INVALID_SOCKET)
	{
		return -1;
	}
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("192.168.0.28"); // 루프백 주소 127.0.0.1
	serveraddr.sin_port = htons(iPort);
	Rv = connect(m_iSocket, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (Rv == SOCKET_ERROR)
	{
		return -1;
	}
	
	linger optval;
	int iLength = sizeof(optval);
	getsockopt(m_iSocket, SOL_SOCKET, SO_LINGER, (char*)&optval, &iLength);
	optval.l_onoff = 1;
	optval.l_linger = 1000;
	setsockopt(m_iSocket, SOL_SOCKET, SO_LINGER, (char*)&optval, iLength);

	int socketType1;
	int typeLen1 = sizeof(socketType1);
	getsockopt(m_iSocket, SOL_SOCKET, SO_TYPE, (char*)&socketType1, &typeLen1);

	if (socketType1 == SOCK_STREAM)
	{
		I_Debug.Print("%s", "SOCK_STREAM.");
	}
	else
	{
		I_Debug.Print("%s", "SOCK_DGRAM");
	}
	getsockopt(m_iSocket, SOL_SOCKET,
		SO_SNDBUF,
		(char*)&socketType1, &typeLen1);
	I_Debug.Print("%s=%d", "SO_SNDBUF", socketType1);

	getsockopt(m_iSocket, SOL_SOCKET, SO_RCVBUF, (char*)&socketType1, &typeLen1);
	I_Debug.Print("%s=%d", "SO_RCVBUF", socketType1);


	return 0;
}

bool SCHAT_Client::Init()
{
	int rv;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return -1;
	}

	if (CreateConnectSocket(10000) == 0)
	{
		// send thread
		unsigned sendThread, receiveThread;
		m_hSendThread = _beginthreadex(NULL, 0, sendMessage, (void*)this, 0, &sendThread);
		// recv thread
		m_hReceiveThread = _beginthreadex(NULL, 0, receiveMessage, (void*)this, 0, &receiveThread);

		int iLevelSend = GetThreadPriority(HANDLE(m_hSendThread));
		int iLeveIRecv = GetThreadPriority(HANDLE(m_hReceiveThread));
		if (SetThreadPriority(HANDLE(m_hReceiveThread), THREAD_PRIORITY_ABOVE_NORMAL == TRUE))
		{
			iLeveIRecv = GetThreadPriority(HANDLE(m_hReceiveThread));
			INT KKK = 0;
		};
		m_bLoginOK = true;
	}
	return true;
}

bool SCHAT_Client::Frame()
{
	if (m_bExit)
	{
		I_Debug.Print("%s", " 서버가 종료 되었습니다.");
		m_bExit = false;
	}
	return true;
}

bool SCHAT_Client::Release()
{
	m_bExit = true;
	closesocket(m_iSocket);

	// send exit wait
	WaitForSingleObject((HANDLE)m_hSendThread, INFINITE);
	// rect exit wait
	WaitForSingleObject((HANDLE)m_hReceiveThread, INFINITE);
	WSACleanup();

	CloseHandle(HANDLE(m_hReceiveThread));
	CloseHandle(HANDLE(m_hSendThread));
	m_hReceiveThread = NULL;
	m_hSendThread = NULL;
	return true;
}

SCHAT_Client::SCHAT_Client(void)
{
	m_bSend = false;
	m_bLoginOK = false;
	m_bExit = false;
	m_iSocket = 0;
	m_hReceiveThread = 0;
	m_hSendThread = 0;
}


SCHAT_Client::~SCHAT_Client(void)
{
}
