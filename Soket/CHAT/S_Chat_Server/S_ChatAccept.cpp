#include "S_ChatAccept.h"
#include "S_Chat_Svr.h"

void S_ChatAccept::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	S_CHAT.AddUser(socket, address);
}


S_ChatAccept::S_ChatAccept()
{
}


S_ChatAccept::~S_ChatAccept()
{
}
