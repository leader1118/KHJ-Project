#pragma once
#include "SPacketPool.h"
typedef struct _OVERLAPPEDEX : OVERLAPPED // 비동기 구조체
{
	enum { MODE_RECV = 0, MODE_SEND=1 }; // 반환 이넘값 어떤일이 떨어졌는지 알수 있다
	int iFlags;
	_OVERLAPPEDEX()
	{
		iFlags = MODE_RECV; // 기본 값을 recv로 계속 받을수 있게한다?
	}
}OVERLAPPEDEX;

class SUser : public SServerObj
{
public:
	SStreamPacket	m_StreamPacket;
	SOCKET			m_Socket;
	C_STR			m_szName;
	SOCKADDR_IN		m_UserAddress;
	WSABUF			m_szRecvBuffer;
	WSABUF			m_szWsaBuf;
	char			m_strBuffer[4096];
	OVERLAPPEDEX	m_ov; // 비동기 구조체 변수
public:
	bool	Create();
	bool	Run();
	virtual void AddPacket(S_PACKET& addPacket);
	virtual void DeleteUser(SOCKET socket);
	virtual void DeleteUser();
	virtual void WaitForPacketReceive();
	virtual void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);
public:
	SUser(void);
	virtual ~SUser(void);
};

