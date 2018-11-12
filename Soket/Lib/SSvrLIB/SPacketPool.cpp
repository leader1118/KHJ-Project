#include "SPacketPool.h"
#include "SLock.h"

// 패킷 풀에 패킷을 저장해준다
bool	SPacketPool::AddPacket(S_PACKET& addPacket)
{
	{
		SLock lock(this);
		m_PacketList.push_back(addPacket);
	}
	return true;
}


bool SPacketPool::ProcessPacket()
{
	{
		SLock lock(this);
		list<S_PACKET>::iterator iter;
		for (iter = m_PacketList.begin();
			iter != m_PacketList.end();
			iter++)
		{
			S_PACKET* pUserData = (S_PACKET*)&(*iter);
			ProcessWork(pUserData);
		}
		return true;
	}
}
void SPacketPool::ProcessWork(S_PACKET* pUserData)
{

}

SPacketPool::SPacketPool()
{
}


SPacketPool::~SPacketPool()
{
}
