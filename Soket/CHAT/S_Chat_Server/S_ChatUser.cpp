#include "S_ChatUser.h"
#include "S_Chat_Svr.h"

void S_ChatUser::MoveMent(UPACKET* pPacket)
{
	SPACKET_USER_POSITION User;
	memcpy(&User, pPacket->msg, sizeof(char)*pPacket->ph.len - 4);
	m_iIndex = User.user_idx;
	m_PositionX = User.PosX;
	m_PositionY = User.PosY;
	m_iDirection = User.direction;
}
void S_ChatUser::AddPacket(PACKET& addPacket)
{
	S_CHAT.m_PacketPool.AddPacket(addPacket);
}
void S_ChatUser::DeleteUser(SOCKET socket)
{
	S_CHAT.DeleteUser(socket);
}
void S_ChatUser::DeleteUser()
{
	S_CHAT.DeleteUser(this);
}

void S_ChatUser::Dispatch(DWORD dwByteSize, LPOVERLAPPED OV)
{
	OVERLAPPEDEX* pOV = (OVERLAPPEDEX*)OV;
	if (dwByteSize == 0)return;
	if (pOV->i_Flags == OVERLAPPEDEX::MODE_RECV)
	{
		m_StreamPacket.Put(m_szRecvBuf.buf, dwByteSize, this);
	}
	if (pOV->i_Flags == OVERLAPPEDEX::MODE_SEND)
	{

	}
	WaitforPacketReceive();
}
S_ChatUser::S_ChatUser()
{
}


S_ChatUser::~S_ChatUser()
{
}
