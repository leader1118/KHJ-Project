#pragma once
#include "SPacketPool.h"
#include "SProtocolChat.h"
class SChatPacketPool : public SPacketPool
{
public:
	void ProcessWork(S_PACKET* pUserData);
public:
	SChatPacketPool(void);
	virtual ~SChatPacketPool(void);
};

