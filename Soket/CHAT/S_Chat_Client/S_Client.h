#pragma once
#include "S_Std.h"
#include "S_Protocol.h"
#include "S_SvrUser.h"

class S_Client : public S_SvrUser
{
public:
	int				m_iSocket;
	unsigned long	m_SendThread;
	unsigned long	m_ReceiveThread;
	bool			m_bExit;
public:
	char			m_strBuf[128];
	bool			m_Send;
	bool			m_LoginOk;
public:
	bool			Init();
	bool			Frame();
	bool			Release();
public:
	int				CreateConnectSocket(int iPort);
	int				SendMsg(char* pmsg, WORD code);
	int				SendMsg(char* pmsg, int iSize, WORD code);
	int				ProcessPacket();
public:
	S_Client();
	~S_Client();
};

