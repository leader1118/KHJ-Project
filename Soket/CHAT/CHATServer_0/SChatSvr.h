#pragma once
#include "SServer.h"
#include "SCHATAccept.h"
#include "SChatUser.h"
#include "SChatPacketPool.h"
class SChatSvr : public SSingleton<SChatSvr>, public SServer
{
private:
	friend class SSingleton<SChatSvr>;
public:
	SChatPacketPool m_PacketPool;
	SCHATAccept		m_Acceptor;

	list<SChatUser*> m_UserList;
	typedef list<SChatUser*>::iterator m_ListItor;
	int		m_iUserCount;
public:
public:
	SChatSvr();
	virtual ~SChatSvr();
};

