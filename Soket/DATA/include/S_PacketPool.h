#pragma once
#include "S_Thread.h"
#include "S_StreamPacket.h"

class S_PacketPool : public S_SvrObj
{
public:
	list<PACKET> m_PacketList;
	typedef list<PACKET>::iterator m_Piter;
public:
	virtual bool AddPacket(PACKET& addPacket);
	virtual bool ProcessPacket();
	virtual void ProcessWork(PACKET* _pUserData);
public:
	S_PacketPool();
	virtual ~S_PacketPool();
};

