#pragma once
#include "S_Acceptor.h"

class S_ChatAccept : public S_Acceptor
{
public:
	void AddUser(SOCKET socket, SOCKADDR_IN address);
public:
	S_ChatAccept();
	virtual ~S_ChatAccept();
};

