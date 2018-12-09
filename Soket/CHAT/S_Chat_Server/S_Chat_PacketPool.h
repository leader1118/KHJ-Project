#pragma once
#include "S_PacketPool.h"
#include "S_Protocol.h"

class S_Chat_PacketPool : public S_PacketPool
{
public:
	void ProcessWork(PACKET* pUserData);
public:
	S_Chat_PacketPool();
	virtual ~S_Chat_PacketPool();
};

