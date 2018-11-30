#pragma once
#include "SAcceptor.h"
class TChatAccept : public SAcceptor
{
public:
	void AddUser(SOCKET socket, SOCKADDR_IN address );
public:
	TChatAccept(void);
	~TChatAccept(void);
};

