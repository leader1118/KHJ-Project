#pragma once
#include "SThread.h"
#include "SStreamPacket.h"
class SPacketPool : public SServerObj
{
public:
	list<S_PACKET> m_PacketList;
	typedef list<S_PACKET>::iterator m_PackItor;
public:
	virtual bool	AddPacket(S_PACKET& addPacket);
	virtual bool	ProcessPacket();
	virtual void	ProcessWork(S_PACKET* pUserData);
public:
	SPacketPool(void);
	virtual ~SPacketPool(void);
};

