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
	bool Init();
	bool Release();
	bool Run();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Print(char*fmt, ...);
	bool AddUser(SOCKET socket, SOCKADDR_IN address);
	void DeleteUser(SOCKET socket);
	void DeleteUser(SChatUser* pUser);
	void Broadcastting(char* msg, WORD code, SOCKET SendSocket = 0);
	void Broadcastting(S_PACKET* pUserData);
	void Broadcastting(UPACKET* pPacket,SOCKET pSendUser=NULL);

public:
	SChatSvr(void);
	virtual ~SChatSvr(void);
};
#define I_Server SChatSvr::GetInstance()

