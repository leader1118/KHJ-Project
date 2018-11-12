#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h> // InetNtop() . inet_ntop()
#include <iostream>
#include <map>
#pragma comment (lib,"ws2_32")
using namespace std;

bool BeginWinSock();
bool EndWinSock();

struct TUser
{
	SOCKET sock;
	SOCKADDR_IN clientAddr;
};

void main()
{
	if (BeginWinSock() == false)
	{
		return;
	}


	
	SOCKET listenSock;
	listenSock = socket(AF_INET,SOCK_STREAM,0);

	// listen socket
	// ip + port -> bind -> �ü�� ����,����,�˸�,�Ű�,����,����
	// port�� ����ϰ� �ִ� ���μ���(�ε����� �Ұ� �ϴ�)(��������)(���������� �����ϴ� �뵵�� ����Ѵ�)���� �˷� �ش�


	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192,168,0,106");
	//sa.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenSock, (sockaddr*)&sa, sizeof(sa));
	listen(listenSock, SOMAXCONN); // -> ����

	u_long on = TRUE;
	ioctlsocket(listenSock,FIONBIO,&on); //FIONBIO ���� X



	std::map<int, TUser>g_userList;

	int g_iNumUser = 0;

	while (g_iNumUser<10)
	{

		TUser tUser;
		
		int iSize = sizeof(tUser.clientAddr);
		tUser.sock = accept(listenSock, (sockaddr*)&tUser.clientAddr, &iSize);  // ������ -> ���ӽõ�
		if (tUser.sock == SOCKET_ERROR)
		{
			if (WSAGetLastError()!=WSAEWOULDBLOCK) //WSAEWOULDBLOCK�� ���� ������ ����
			{
				exit(1);
			}
		}
		else
		{
			g_userList.insert(make_pair(g_iNumUser++, tUser));
			// Use inet_ntop() or lnetNtop()
			printf("\nip=%s,port=%d", inet_ntoa(tUser.clientAddr.sin_addr),
				ntohs(tUser.clientAddr.sin_port));
		}
			
			//char ip[INET_ADDRSTRLEN] = { 0, };
		//char ip[256] = { 0, };
		//printf("\nip=%s,port=%d", inet_ntop(AF_INET, &clientAddr.sin_addr, ip, INET6_ADDRSTRLEN),
		//	ntohs(clientAddr.sin_port));

	}
	while (1)
	{
		char recvmsg[256] = { 0, };
		int iRecvByte = sizeof(recvmsg);
		TUser* pUser 
		for (int iUser = 0; iUser < g_userList.size(); iUser++)
		{
			int iByte = recv(g_userList[iUser].sock, recvmsg, iRecvByte, 0);

			printf("\nip=%s,port=%d", inet_ntoa(g_userList[iUser].clientAddr.sin_addr),
				//ntohs(g_userList[iUser].clientAddr.sin_addr,recvmsg);
			send(g_userList[iUser].sock, recvmsg, iRecvByte, 0);
		}
	}
	char msg[] = "���������մϴ�. !!!";
	int iSebdByte = sizeof(msg);
	for (int iUser = 0; iUser < g_userList.size();)
	{
		send(g_userList[iUser].sock, msg, iSebdByte,0);
	}

	for (int iUser = 0; iUser < g_userList.size();)
	{
		closesocket(g_userList[iUser].sock);
	}
	closesocket(listenSock);

	// listen -> ���.
	// client socket �غ�
	// while(1)
	// client socket = accept // ������ -> ���ӽõ�.����õ� -> ����,�㰡
	
	
	EndWinSock();
}

bool BeginWinSock() // ���� �ʱ�ȭ

{
	WSADATA wsa;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iRet != 0)return false;
	return true;
}

bool EndWinSock() // ���� �Ҹ�
{
	WSACleanup();
	return true;
}