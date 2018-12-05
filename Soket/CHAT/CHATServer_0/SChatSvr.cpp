#include "SChatSvr.h"
#include "SServerIOCP.h"
#include "SDebugString.h"
#include "SLock.h"
#include "TStd.h"
#include "SServer.h"

bool SChatSvr::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	{
		SLock Lock(this);
		SChatUser* pUser = NULL;
		SAFE_NEW(pUser, SChatUser);

		pUser->m_Socket = socket;
		pUser->m_UserAddress = address;

		I_Debug.Print("IP = %s,PORT =%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

		if (pUser)
		{
			I_Server.SendMsg(pUser->m_Socket,
				"�������!",
				PACKET_CHAR_NAME_REQ);
			m_UserList.push_back(pUser);

			I_ServerIOCP.AddHandleToIOCP((HANDLE)socket, (ULONG_PTR)pUser);
			pUser->Create();
		}
	}
	return true;
}
void SChatSvr::DeleteUser(SOCKET socket)
{
	{
		SLock Lock(this);
		list<SChatUser*>::iterator iter;
		list<SChatUser*>::iterator DelUser;

		int iClientUser = I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			SChatUser* pUser = (SChatUser*)*iter;
			if (pUser->m_Socket == socket)
			{
				char buffer[256] = { 0, };
				sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "���� �����ϼ˽��ϴ�.");
				I_Debug.Print("%s%s", pUser->m_szName.c_str(), "���� �����ϼ˽��ϴ�.");
				I_Server.Broadcastting(buffer, PACKET_CHAR_MSG, pUser->m_Socket);
				closesocket(pUser->m_Socket);
				DelUser = iter;
				SAFE_DEL(pUser);
				break;
			}
		}
		I_Server.m_UserList.erase(DelUser);
	}
}

void SChatSvr::DeleteUser(SChatUser* pDeleteUser)
{
	{
		SLock Lock(this);
		list<SChatUser*>::iterator iter;
		list<SChatUser*>::iterator DelUser;

		int iClientUser = (int)I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			SChatUser* pUser = (SChatUser*)*iter;
			if (pUser == pDeleteUser)
			{
				char buffer[256] = { 0, };
					sprintf_s(buffer, "%s%s", pUser->m_szName.c_str(), "���� �����ϼ˽��ϴ�.");
					I_Debug.Print("%s%s", pUser->m_szName.c_str(), "���� �����ϼ˽��ϴ�.");
					I_Server.Broadcastting(buffer, PACKET_CHAR_MSG, pUser->m_Socket);
					closesocket(pUser->m_Socket);
					DelUser = iter;
					SAFE_DEL(pUser);
					break;
			}
		}
		I_Server.m_UserList.erase(DelUser);
	}
}

void SChatSvr::Broadcastting(char * msg, WORD code, SOCKET SendSocket)
{
	{
		SLock Lock(this);
		list<SChatUser*>::iterator iter;
		list<SChatUser*>::iterator DelUser;

		int iClientUser = (int)I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			SChatUser*pUser = (SChatUser*)*iter;
			if (0 == SendSocket || pUser->m_Socket != SendSocket)
			{
				if (!SendMsg(pUser->m_Socket, msg, code))
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			I_Debug.Print("%s%s%s", pUser->m_szName.c_str(), msg, "���½��ϴ�.");
		}
	}
}

void SChatSvr::Broadcastting(UPACKET* pPacket, SOCKET pSendUser)
{
	{
		SLock Lock(this);
		list<SChatUser*>::iterator iter;
		list<SChatUser*>::iterator DelUser;

		int iClientUser = (int)I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			SChatUser* pUser = (SChatUser*)*iter;
			int iRet = send(pUser->m_Socket, (char*)pPacket, pPacket->ph.len, 0);
			if (iRet < 0)
			{
				I_Debug.T_ERROR(false);
				continue;
			}
			I_Debug.Print("%s �� ���½��ϴ�.", pPacket->msg);
		}
	}
}
void SChatSvr::Broadcastting(S_PACKET* pUserData)
{
	{
		SLock Lock(this);
		list<SChatUser*>::iterator iter;
		list<SChatUser*>::iterator DelUser;

		UPACKET* pPacket = &pUserData->packet;
		//DWORD dwSendByte;
		int iClientUser =(int)I_Server.m_UserList.size();
		for (iter = I_Server.m_UserList.begin();
			iter != I_Server.m_UserList.end();
			iter++)
		{
			SChatUser* pUser = (SChatUser*)*iter;
			if (pUser->m_Socket != pUserData->pUser->m_Socket)
			{
				int iRet = send(pUser->m_Socket, (char*)&pUserData->packet, pUserData->packet.ph.len, 0);
				if (iRet < 0)
				{
					I_Debug.T_ERROR(false);
					continue;
				}
			}
			I_Debug.Print("%s���� %s�� ���½��ϴ�.", pUser->m_szName.c_str(), pUserData->packet.msg);
		}
	}
}

bool SChatSvr::Init()
{
	I_Debug.Print("%s", "ä�� ����");
	SServer::Init();
	m_Acceptor.Set(10000, NULL);
	return true;
}
bool SChatSvr::Release()
{
	return SServer::Release();
}

bool SChatSvr::Run()
{
	while (m_bStarted)
	{
		m_PacketPool.ProcessPacket();
		Sleep(10);
	}
	return true;
}
SChatSvr::SChatSvr(void)
{
}


SChatSvr::~SChatSvr(void)
{
}
