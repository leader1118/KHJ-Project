#include "S_Chat_Svr.h"
#include "S_IOCP.h"
#include "S_DebugString.h"

bool S_Chat_Svr::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	{
		S_Lock Lock(this);
		S_ChatUser* pUser = NULL;
		SAFE_NEW(pUser, S_ChatUser);
		pUser->m_Socket = socket;
		pUser->m_UserAddr = address;

		S_Debug.Print("IP=%s, PORT=%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

		if (pUser)
		{
			S_CHAT.SendMsg(pUser->m_Socket, "어서오세요! 채팅을 입력해주세요", PACEKT_CHAT_NAME_REQ);
			m_UserList.push_back(pUser);
			S_iocp.AddhandleToIOCP((HANDLE)socket, (ULONG_PTR)pUser);
			pUser->Create();


		}
	}
	return true;
}

void S_Chat_Svr::DeleteUser(SOCKET socket)
{
	{
		S_Lock Lock(this);
		list<S_ChatUser*>::iterator iter;
		list<S_ChatUser*>::iterator delUser;

		int iClientUser = (int)S_CHAT.m_UserList.size();
		for (iter = S_CHAT.m_UserList.begin();
			iter != S_CHAT.m_UserList.end();
			iter++)
		{
			S_ChatUser* pUser=(S_ChatUser*)*iter;
			if (pUser->m_Socket = socket)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s,%s", pUser->m_szname.c_str(), "님이 나가셧습니다.");
				S_Debug.Print("%s,%s", pUser->m_szname.c_str(), "님이 나가셧습니다.");
				S_CHAT.Broadcastting(buffer, PACKET_CHAT_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				delUser = iter;
				SAFE_DELETE(pUser);
				break;
			}
		}
		S_CHAT.m_UserList.erase(delUser);
	}
}

void S_Chat_Svr::DeleteUser(S_ChatUser* pDeleteUser)
{
	S_Lock Lock(this);
	list<S_ChatUser*>::iterator iter;
	list<S_ChatUser*>::iterator delUser;

	int iClientUser = (int)S_CHAT.m_UserList.size();
	for (iter = S_CHAT.m_UserList.begin();
		iter != S_CHAT.m_UserList.end();
		iter++)
	{
		S_ChatUser* pUser = (S_ChatUser*)*iter;
		if (pUser == pDeleteUser)
		{
			char buffer[256] = { 0, };
			sprintf_s(buffer, "%s,%s", pUser->m_szname.c_str(), "님이 나가셧습니다.");
			S_Debug.Print("%s,%s", pUser->m_szname.c_str(), "님이 나가셧습니다.");
			S_CHAT.Broadcastting(buffer, PACKET_CHAT_MSG, pUser->m_Socket);
			closesocket(pUser->m_Socket);
			delUser = iter;
			SAFE_DELETE(pUser);
			break;
		}
		S_CHAT.m_UserList.erase(delUser);
	}
}

void S_Chat_Svr::Broadcastting(UPACKET* pPacket, SOCKET pSendUser)
{
	{
		S_Lock Lock(this);
		list<S_ChatUser*>::iterator iter;
		list<S_ChatUser*>::iterator delUser;

		int iClientUser = (int)S_CHAT.m_UserList.size();
		for (iter = S_CHAT.m_UserList.begin();
			iter != S_CHAT.m_UserList.end();
			iter++)
		{
			S_ChatUser* pUser = (S_ChatUser*)*iter;
			{
				int iRet = send(pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
				if (iRet < 0)
				{
					S_Debug.S_Error(false);
					continue;
				}
			}
			S_Debug.Print("%s 에게 %s 보냈습니다.", pUser->m_szname.c_str(), pPacket->msg);
		}
	}
}

void S_Chat_Svr::Broadcastting(PACKET* pUserData)
{
	{
		S_Lock Lock(this);
		list<S_ChatUser*>::iterator iter;
		list<S_ChatUser*>::iterator delUser;

		UPACKET* pPacket = &pUserData->packet;
		int iClientUser = (int)S_CHAT.m_UserList.size();
		for (iter = S_CHAT.m_UserList.begin();
			iter != S_CHAT.m_UserList.end();
			iter++)
		{
			S_ChatUser* pUser = (S_ChatUser*)*iter;
			if (pUser->m_Socket != pUserData->pUser->m_Socket)
			{
				int iRet = send(pUser->m_Socket, (char*)&pUserData->packet, pUserData->packet.ph.len, 0);
				if (iRet < 0)
				{
					S_Debug.S_Error(false);
					continue;
				}
			}
			S_Debug.Print("%s 에게 %s 님의 %s 보냈습니다.", pUser->m_szname.c_str(),
				pUserData->pUser->m_szname.c_str(),
				pUserData->packet.msg);
		}
	}
}

void S_Chat_Svr::Broadcastting(char* msg, WORD code, SOCKET SendSocket)
{
	{
		S_Lock Lock(this);
		list<S_ChatUser*>::iterator iter;
		list<S_ChatUser*>::iterator delUser;

		int iClientUser = (int)S_CHAT.m_UserList.size();
		for (iter = S_CHAT.m_UserList.begin();
			iter != S_CHAT.m_UserList.end();
			iter++)
		{
			S_ChatUser* pUser = (S_ChatUser*)*iter;
			if (0 == SendSocket || pUser->m_Socket != SendSocket)
			{
				if (!SendMsg(pUser->m_Socket, msg, code))
				{
					S_Debug.S_Error(false);
					continue;
				}
			}
			S_Debug.Print("%s %s %s", pUser->m_szname.c_str(), msg, "보냈습니다");
		}
	}
}

bool S_Chat_Svr::Init()
{
	S_Debug.Print("%s", "서버 시작");
	S_Server::Init();
	m_Acceptor.Set(10000, NULL);
	return true;
}

bool S_Chat_Svr::Release()
{
	return S_Server::Release();
}

bool S_Chat_Svr::Run()
{
	while (m_bStarted)
	{
		m_PacketPool.ProcessPacket();
		Sleep(10);
	}
	return true;
}
S_Chat_Svr::S_Chat_Svr()
{
}


S_Chat_Svr::~S_Chat_Svr()
{
}
