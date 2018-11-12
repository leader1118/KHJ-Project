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
	// ip + port -> bind -> 운영체제 보고,통지,알림,신고,적용,세팅
	// port를 사용하고 있는 프로세스(인덱스에 불가 하다)(실행파일)(실행파일을 구분하는 용도로 사용한다)에게 알려 준다


	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192,168,0,106");
	//sa.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenSock, (sockaddr*)&sa, sizeof(sa));
	listen(listenSock, SOMAXCONN); // -> 개통

	u_long on = TRUE;
	ioctlsocket(listenSock,FIONBIO,&on); //FIONBIO 블럭형 X



	std::map<int, TUser>g_userList;

	int g_iNumUser = 0;

	while (g_iNumUser<10)
	{

		TUser tUser;
		
		int iSize = sizeof(tUser.clientAddr);
		tUser.sock = accept(listenSock, (sockaddr*)&tUser.clientAddr, &iSize);  // 누군가 -> 접속시도
		if (tUser.sock == SOCKET_ERROR)
		{
			if (WSAGetLastError()!=WSAEWOULDBLOCK) //WSAEWOULDBLOCK와 같지 않으면 오류
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
	char msg[] = "게임종료합니다. !!!";
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

	// listen -> 듣다.
	// client socket 준비
	// while(1)
	// client socket = accept // 누군가 -> 접속시도.연결시도 -> 수용,허가
	
	
	EndWinSock();
}

bool BeginWinSock() // 윈속 초기화

{
	WSADATA wsa;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iRet != 0)return false;
	return true;
}

bool EndWinSock() // 윈속 소멸
{
	WSACleanup();
	return true;
}