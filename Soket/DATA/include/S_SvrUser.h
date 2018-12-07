#pragma once
#include "S_PacketPool.h"

class S_SvrUser : public S_SvrObj
{
public:
	S_StreamPacket	m_StreamPacket;
	SOCKET			m_Socket;
	C_STR			m_szname;
	SOCKADDR_IN		m_UserAddr;
	WSABUF			m_szRecvBuf;
	WSABUF			m_szWSABuf;
	char			m_strBuffer[4096];
	OVERLAPPEDEX	m_OV;
public:
	bool Create();
	bool Run();
	virtual void AddPacket(PACKET& addPacket);
	virtual void DeleteUser(SOCKET socket);
	virtual void DeleteUser();
	virtual void WaitforPacketReceive();
	virtual void Dispatch(DWORD dwByteSize, LPOVERLAPPED Ov);
public:
	S_SvrUser();
	virtual ~S_SvrUser();
};

