#pragma once
#include "SThread.h"
class SAcceptor : public SThread
{
public:
	SOCKET			m_ListenSock; // ���� ����
public:
	bool			Run(); // ������ �Լ�
	bool			Release(); // �Ҹ��Լ�
	bool			Set(int iPort, const char* strAddress = 0); // ��Ʈ�� �ּҸ� ���� �ϴ� �Լ�
	virtual void	AddUser(SOCKET socket, SOCKADDR_IN address); //  ���� �߰��ϴ� �Լ�
public:
	SAcceptor(void);
	virtual ~SAcceptor(void);
};

