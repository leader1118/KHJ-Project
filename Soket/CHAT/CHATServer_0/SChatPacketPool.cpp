#include "SChatPacketPool.h"
#include "SChatUser.h"
#include "SDebugString.h"
#include "SChatSvr.h"
#include "SChatUser.h"

void SChatPacketPool::ProcessWork(S_PACKET* pUserData)
{
	UPACKET* pPacket = &(pUserData->packet);
	SChatUser* pUser = (SChatUser*)pUserData->pUser;
	switch (pPacket->ph.type)
	{
	case PACKET_USER_POSITION:
	{
		pUser->Movement(pPacket);
		I_Server
	}
	}
}


SChatPacketPool::SChatPacketPool(void)
{
}


SChatPacketPool::~SChatPacketPool(void)
{
}
