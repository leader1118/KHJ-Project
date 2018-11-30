#pragma once
#include "SPacketPool.h"
#include "TProtocolChat.h"

class TChatPacketPool : public SPacketPool
{
public:
	void		ProcessWork(S_PACKET* pUserData);
public:
	TChatPacketPool(void);
	~TChatPacketPool(void);
};

