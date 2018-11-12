#pragma once
#include "SServerObj.h"
#include "SProtocol.h"
#define MAX_RECV_SIZE 10000
class SUser;
typedef struct
{
	UPACKET packet;
	SUser*	pUser;
}S_PACKET, *P_SPACKET;

class SStreamPacket : public SServerObj
{
public:
	list<S_PACKET> m_PacketList;
	typedef list<S_PACKET>::iterator m_PackItor; // ��Ŷ ����Ʈ�� ������ �ִ´�
public:
	UPACKET*				m_pPacket;
	char					m_RecvBuffer[MAX_RECV_SIZE];
	int						m_iStartPos;
	int						m_iWritePos;
	int						m_iReadPos;
public:
	void	Put(char* recvBuffer, int iSize, SUser* = NULL);
public:
	SStreamPacket();
	virtual ~SStreamPacket();
};

