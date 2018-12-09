#pragma once
#include "S_SvrUser.h"
class S_ChatUser : public S_SvrUser
{
public:
	int m_iIndex;
	int m_PositionX;
	int m_PositionY;
	int m_iDirection;
public:
	void MoveMent(UPACKET* pPacket);
	void AddPacket(PACKET& addPacket);
	void DeleteUser(SOCKET socket);
	void DeleteUser();
	void Dispatch(DWORD dwByteSize, LPOVERLAPPED OV);
public:
	S_ChatUser();
	virtual ~S_ChatUser();
};

