#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#pragma comment (lib,"ws2_32.lib")

// 소켓 생성
// 연결형, TCP 프로토콜(sock_STREAM,IPPROTO_TCP)
// 비연결형, UDP 프로토콜(sock_DGRAM,IPPROTO_UDP)

int main(int argc, char*argv[])
{
	unsigned short iPort = 10000;
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	// 소켓을 대상 ip에 연결해라.
	iRet = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return -1;
	iRet = listen(listenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR)return -1;
	SOCKADDR_IN clientaddr;
	SOCKET client;
	while (1)
	{
		int addlen = sizeof(clientaddr);
		client = accept(listenSock, (SOCKADDR*)&clientaddr, &addlen);
		printf("클라이언트 접속 : IP:%s, PORT:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		char buf[256] = { 0, };
		int iLen = 0;
		while (1)
		{
			int iRecvByte = recv(client, buf, 256, 0);
			if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
			{
				printf("클라이언트 접속 종료 :IPL%s,PORT:%d\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port));
				break;
			}
			buf[iRecvByte] = '\n';
			printf("\n%s", buf);
			int iSendByte = send(client, buf, iRecvByte, 0);
		}
		closesocket(client);
	}
	closesocket(listenSock);
	// 윈속 소멸
	iRet = WSACleanup();
	return iRet;
	
}