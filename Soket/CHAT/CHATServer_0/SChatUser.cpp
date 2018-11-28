#include "SChatUser.h"
#include "SChatSvr.h"


void SChatUser::Movement(UPACKET* pPacket)
{
	SPACKET_USER_POSITION user;
	memcpy(&user, pPacket->msg, sizeof(char)*pPacket->ph.len - 4);
	m_iIndex = user.user_idx;
	m_PositionX = user.PosX;
	m_PositionY = user.PosY;
	m_iDirection = user.direction;
}
void SChatUser::AddPacket(S_PACKET& addPacket)
{
	I_Server.m_PacketPool.AddPacket(addPacket);
}
void SChatUser::DeleteUser(SOCKET socket)
{
	I_Server.DeleteUser(socket);
}
void SChatUser::DeleteUser()
{
	I_Server.DeleteUser(this);
}
void SChatUser::Dispatch(DWORD dwByteSize, LPOVERLAPPED ov)
{
	OVERLAPPEDEX* pOV = (OVERLAPPEDEX*)ov;
	if (dwByteSize == 0)return;
	if (pOV->iFlags == OVERLAPPEDEX::MODE_RECV)
	{
		m_StreamPacket.Put(m_szRecvBuffer.buf, dwByteSize, this);
	}
	if (pOV->iFlags == OVERLAPPEDEX::MODE_SEND)
	{

	}
	WaitForPacketReceive();
}


SChatUser::SChatUser(void)
{
}


SChatUser::~SChatUser(void)
{
}
