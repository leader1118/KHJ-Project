#include "SCHATAccept.h"
#include "SChatSvr.h"
void SCHATAccept::AddUser(SOCKET socket, SOCKADDR_IN address)
{
	I_Server.AddUser(socket, address);
}

SCHATAccept::SCHATAccept(void)
{
}


SCHATAccept::~SCHATAccept(void)
{
}
