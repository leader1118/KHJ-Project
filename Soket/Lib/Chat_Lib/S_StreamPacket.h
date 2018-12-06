#pragma once
#include "S_Std.h"
#include "S_Protocol.h"

class S_StreamPacket
{
public:
	list<PACKET> PacketList;
	typedef list<PACKET>::iterator itor;
public:
	UPACKET* m_pPacket;
	int m_iStartPos;
	int m_iWritePos;
	int m_iReadPos;
	char RecvBuffer[10000];
public:
	void Put(char* recvBuffer, int Size, S_SvrUser* = NULL);
public:
	S_StreamPacket();
	virtual ~S_StreamPacket();
};

