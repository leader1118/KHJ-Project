#include "S_PacketPool.h"

bool S_PacketPool::AddPacket(PACKET& addPacket)
{
	{
		S_Lock Lock(this);
		m_PacketList.push_back(addPacket);
	}
	return true;
}
bool S_PacketPool::ProcessPacket()
{
	{
		S_Lock Lock(this);
		list<PACKET>::iterator itor;
		for (itor = m_PacketList.begin();
			itor != m_PacketList.end();
			itor++)
		{
			PACKET* UserData = (PACKET*)&(*itor);
			ProcessWork(UserData);
		}
		m_PacketList.clear();
	}
	return true;
}

void S_PacketPool::ProcessWork(PACKET* UserData)
{

}

S_PacketPool::S_PacketPool()
{
}


S_PacketPool::~S_PacketPool()
{
}
