#pragma once
#include "SAcceptor.h"
class SCHATAccept : public SAcceptor
{
public:
	void AddUser(SOCKET socket, SOCKADDR_IN address);
public:
	SCHATAccept(void);
	virtual ~SCHATAccept(void);
};

