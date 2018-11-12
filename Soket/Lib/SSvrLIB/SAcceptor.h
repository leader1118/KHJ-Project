#pragma once
#include "SThread.h"
class SAcceptor : public SThread
{
public:
	SOCKET			m_ListenSock; // 소켓 생성
public:
	bool			Run(); // 돌리는 함수
	bool			Release(); // 소멸함수
	bool			Set(int iPort, const char* strAddress = 0); // 포트와 주소를 세팅 하는 함수
	virtual void	AddUser(SOCKET socket, SOCKADDR_IN address); //  유저 추가하는 함수
public:
	SAcceptor(void);
	virtual ~SAcceptor(void);
};

