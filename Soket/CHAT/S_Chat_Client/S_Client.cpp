#include "S_Client.h"
#include "S_DebugString.h"

unsigned __stdcall sendMessage(void* arg)
{
	S_Debug.Print("%s", "send 스레드 시작");

	S_Client* pClient = (S_Client*)arg;

	while (!pClient->m_bExit)
	{
		if (pClient->m_LoginOk && pClient->m_Send)
		{
			if (pClient->SendMsg(pClient->m_strBuf, PACKET_CHAT_MSG) <= 0)
			{
				break;
			}
			pClient->m_Send = false;
		}
		if (SwitchToThread() == FALSE)
		{
			Sleep(1);
		}
	}
	return 0;
}

unsigned __stdcall receiveMessage(void* arg)
{
	S_Debug.Print("%s", "receive 스레드 시작");
	S_Client* pClient = (S_Client*)arg;
	int iSocket = pClient->m_iSocket;
	char strBuffer[2048] = { 0, };

	while (!pClient->m_bExit)
	{
		int iRet = recv(iSocket, strBuffer, sizeof(strBuffer), 0);
		if (iRet <= 0)
		{
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
		if (SwitchToThread() == FALSE)
		{
			Sleep(1);
		}
	}
	return 0;
}

int S_Client::ProcessPacket()
{
	{
		S_Lock Lock(this);
		list<PACKET>::iterator iter;
		for (iter = m_StreamPacket.PacketList.begin();
			iter != m_StreamPacket.PacketList.end();
			iter++)
		{
			UPACKET* pPacket = &(*iter).packet;
			switch (pPacket->ph.type)
			{
			case PACEKT_CHAT_NAME_REQ:
			{
				S_Debug.Print("%s", pPacket->msg);
			}break;
			case PACKET_CHAT_MSG:
			{
				S_Debug.Print("%s", pPacket->msg);
			}break;
			}
		}
		m_StreamPacket.PacketList.clear();
	}
	return 1;
}

int S_Client::SendMsg(char* pmsg, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sprintf_s(sendmsg.msg, pmsg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + strlen(sendmsg.msg);
	int iRet = send(m_iSocket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		m_Send = false;

		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		return 0;
	}
	m_Send = false;
	return 1;
}

int S_Client::SendMsg(char* pmsg, int iSize, WORD code)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	memcpy(sendmsg.msg, pmsg, iSize);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + iSize;
	int iRet = send(m_iSocket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		m_Send = false;
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		return 0;
	}
	m_Send = false;
	return 1;
}

int S_Client::CreateConnectSocket(int iPort)
{
	int Rv;
	m_iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_iSocket == INVALID_SOCKET)
	{
		return -1;
	}
	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
		S_Debug.Print("%s", "SOCK_STREAM");
	}
	else
	{
		S_Debug.Print("%s", "SOCk_DGRAM");
	}
	getsockopt(m_iSocket, SOL_SOCKET, SO_SNDBUF, (char*)&socketType1, &typeLen1);
	S_Debug.Print("%s=%d", "SO_RCVBUF", socketType1);

	return 0;
}

bool S_Client::Init()
{
	int RV;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return -1;
	}
	if (CreateConnectSocket(10000) == 0)
	{
		unsigned sendThread, receiveThread;
		m_SendThread = _beginthreadex(NULL, 0, sendMessage, (void*)this, 0, &sendThread);
		m_ReceiveThread = _beginthreadex(NULL, 0, receiveMessage, (void*)this, 0, &receiveThread);

		int iLevelSend = GetThreadPriority(HANDLE(m_SendThread));
		int iLevelRecv = GetThreadPriority(HANDLE(m_ReceiveThread));
		if (SetThreadPriority(HANDLE(m_ReceiveThread), THREAD_PRIORITY_ABOVE_NORMAL == TRUE))
		{
			iLevelRecv = GetThreadPriority(HANDLE(m_ReceiveThread));
			INT sss = 0;
		}
		m_LoginOk = true;
	}
	return true;
}

bool S_Client::Frame()
{
	if (m_bExit)
	{
		S_Debug.Print("%s", "서버 종료");
		m_bExit = false;
	}
	return true;
}

bool S_Client::Release()
{
	m_bExit = true;
	closesocket(m_iSocket);

	WaitForSingleObject((HANDLE)m_SendThread, INFINITE);
	WaitForSingleObject((HANDLE)m_ReceiveThread, INFINITE);
	WSACleanup();

	CloseHandle(HANDLE(m_ReceiveThread));
	CloseHandle(HANDLE(m_SendThread));
	m_ReceiveThread = NULL;
	m_SendThread = NULL;
}

S_Client::S_Client()
{
	m_Send = false;
	m_LoginOk = false;
	m_bExit = false;
	m_iSocket = 0;
	m_ReceiveThread = 0;
	m_SendThread = 0;
}


S_Client::~S_Client()
{
}
