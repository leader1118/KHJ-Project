#pragma once
#include "SvrStd.h"
#include <process.h>
#include "sProtocolClient.h"
#include "SUser.h"
class SCHAT_Client : public SUser
{
public:
	int					m_iSocket;
	unsigned long		m_hSendThread;
	unsigned long		m_hReceiveThread;
	bool				m_bExit;
public:
	char	m_strBuffer[128];
	bool	m_bSend;
	bool	m_bLoginOK;
public:
	bool	Init();
	bool	Frame();
	bool	Release();
public:
	int		CreateConnectSocket(int iPort);
	int		SendMsg(char* pMsg, WORD code);
	int		SendMsg(char* pMsg, int iSize, WORD code);
	int		ProcessPacket();
public:
	SCHAT_Client(void);
	virtual ~SCHAT_Client(void);
};

