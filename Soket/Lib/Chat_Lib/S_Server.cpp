#include "S_Server.h"

bool S_Server::Init()
{
	CreateThread();
	return true;
}
bool S_Server::Release()
{
	return true;
}
bool S_Server::Run()
{
	return true;
}
bool S_Server::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	return true;
}

bool S_Server::SendMsg(SOCKET socket,const  char* msg, WORD code)
{
	UPACKET Sendmsg;
	ZeroMemory(&Sendmsg, sizeof(Sendmsg));
	sprintf_s(Sendmsg.msg, "%s", msg);
	Sendmsg.ph.type = code;
	Sendmsg.ph.len = sizeof(PACKET_HEADER) + strlen(Sendmsg.msg);

	int ret = send(socket, (char*)&Sendmsg, Sendmsg.ph.len, 0);
	if (ret <= 0)
	{
		return false;
	}
	return true;
}
S_Server::S_Server()
{
}


S_Server::~S_Server()
{
}
