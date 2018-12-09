#include "S_Chat_PacketPool.h"
#include "S_ChatUser.h"
#include "S_Chat_Svr.h"
#include "S_DebugString.h"

void  S_Chat_PacketPool::ProcessWork(PACKET* pUserData)
{
	UPACKET* pPacket = &(pUserData->packet);
	S_ChatUser* pUser = (S_ChatUser*)pUserData->pUser;
	switch (pPacket->ph.type)
	{
	case PACKET_USER_POSITION:
	{
		pUser->MoveMent(pPacket); 
		S_CHAT.Broadcastting(pPacket, pUser->m_Socket);
	}break;
	case PACKET_CHAT_NAME_ACK:
	{
		pUser->m_szname = pPacket->msg;
		char buffer[256] = { 0, };
		sprintf_s(buffer, "[%s]%s", pUser->m_szname.c_str(), "´ÔÀÌ µé¾î¿À¼Ë½À´Ï´Ù");
		ZeroMemory(pPacket->msg, 2048);
		sprintf_s(pPacket->msg, "%s", buffer);
		
		pPacket->ph.len = WORD(sizeof(PACKET_HEADER) + strlen(buffer));
		pPacket->ph.type = PACKET_CHAT_MSG;
		S_CHAT.Broadcastting(pPacket, pUser->m_Socket);
	}break;
	case PACKET_CHAT_MSG:
	{
		S_CHAT.Broadcastting(pPacket, pUser->m_Socket);
	}break;
	}
}

S_Chat_PacketPool::S_Chat_PacketPool()
{
}


S_Chat_PacketPool::~S_Chat_PacketPool()
{
}
