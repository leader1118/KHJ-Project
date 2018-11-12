#include "SServer.h"

bool SServer::SendMsg(SOCKET socket, char* msg, WORD code) // 보내기
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	// sprintf (sendmsg.msg, "%s",msg);
	sprintf_s(sendmsg.msg, "%s", msg);
	sendmsg.ph.type = code;
	sendmsg.ph.len = sizeof(PACKET_HEADER) + strlen(sendmsg.msg);
	
	int iRet = send(socket, (char*)&sendmsg, sendmsg.ph.len, 0);
	if (iRet <= 0)
	{
		return false;
	}
	return true;
}

bool SServer::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	return true;
}
bool SServer::Init()
{
	// 쓰레드 생성
	CreateThread();
	return true;
}
bool SServer::Run()
{
	return true;
}
bool SServer::Release()
{
	return true;
}
SServer::SServer(void)
{
}


SServer::~SServer(void)
{
}
