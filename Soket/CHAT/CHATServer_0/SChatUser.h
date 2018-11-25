#pragma once
#include "SUser.h"
class SChatUser : public SUser
{
public:
	int			m_iIndex;
	int			m_PositionX;
	int			m_PositionY;
	int			m_iDirection;
public:
	void Movement(UPACKET* pPacket);
	void AddPacket(S_PACKET& addPacket);
	void DeleteUser(SOCKET socket);
	void DeleteUser();
	void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);
public:
	SChatUser(void);
	virtual ~SChatUser(void);
};

