#pragma once
#include "S_Server.h"
#include "S_Chat_PacketPool.h"
#include "S_ChatAccept.h"
#include "S_ChatUser.h" 

class S_Chat_Svr : public S_Server,public Singleton<S_Chat_Svr>
{
	friend class Singleton<S_Chat_Svr>;
public:
	S_Chat_PacketPool		m_PacketPool;
	S_ChatAccept			m_Acceptor;
	list<S_ChatUser*>		m_UserList;
	typedef list<S_ChatUser*>::iterator m_Listitor;
	int						m_iUserCount;
public:
	bool Init();
	bool Release();
	bool Run();
public:
	bool AddUser(SOCKET socket, SOCKADDR_IN address);
	void DeleteUser(SOCKET socket);
	void DeleteUser(S_ChatUser* pDeleteUser);
	void Broadcastting(char* msg, WORD code, SOCKET SendSocket = 0);
	void Broadcastting(PACKET* pUserData);
	void Broadcastting(UPACKET* pPacket, SOCKET pSendUser = NULL);
public:
	S_Chat_Svr();
	virtual ~S_Chat_Svr();
};
#define S_CHAT S_Chat_Svr::GetInstance()

