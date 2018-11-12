#pragma once
#include "SPacketPool.h"
typedef struct _OVERLAPPEDEX : OVERLAPPED // �񵿱� ����ü
{
	enum { MODE_RECV = 0, MODE_SEND=1 }; // ��ȯ �̳Ѱ� ����� ���������� �˼� �ִ�
	int iFlags;
	_OVERLAPPEDEX()
	{
		iFlags = MODE_RECV; // �⺻ ���� recv�� ��� ������ �ְ��Ѵ�?
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
	OVERLAPPEDEX	m_ov; // �񵿱� ����ü ����
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

