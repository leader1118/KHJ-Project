#include "SChatPacketPool.h"
#include "SChatUser.h"
#include "SDebugString.h"
#include "SChatSvr.h"


void SChatPacketPool::ProcessWork(S_PACKET* pUserData)
{
	UPACKET* pPacket = &(pUserData->packet);
	SChatUser* pUser = (SChatUser*)pUserData->pUser;
	switch (pPacket->ph.type)
	{
	case PACKET_USER_POSITION:
		{
			pUser->Movement(pPacket);
			I_Server.Broadcastting(pPacket, pUser->m_Socket);
		}break;
	case PACKET_CHAR_NAME_ACK:
		{
			pUser->m_szName = pPacket->msg;
			char buffer[256] = { 0, };
			sprintf_s(buffer, "[%s]%s", pUser->m_szName.c_str(), "´ÔÀÌ µé¾î¿À¼Ë½À´Ï´Ù.");
			ZeroMemory(pPacket->msg, 2048);
			sprintf_s(pPacket->msg, "%s", buffer);
			pPacket->ph.len = sizeof(PACKET_HEADER) + strlen(buffer);
			pPacket->ph.type = PACKET_CHAR_MSG;
			
			I_Server.Broadcastting(pPacket, pUser->m_Socket);
		}break;
	case PACKET_CHAR_MSG:
		{
			I_Server.Broadcastting(pPacket, pUser->m_Socket);
		}break;
	}
}


SChatPacketPool::SChatPacketPool(void)
{
}


SChatPacketPool::~SChatPacketPool(void)
{
}
