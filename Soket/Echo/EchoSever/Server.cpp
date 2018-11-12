#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h> // InetNtop() . inet_ntop()
#include <iostream>
#include <map>
#include "TProtocol.h"
#pragma comment (lib,"ws2_32")
using namespace std;

bool BeginWinSock();
bool EndWinSock();

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
	memcpy(sendmsg.msg, msg, strlen(msg));
	int sendbytes = 0;
	int iTotalsize = strlen(msg) + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&sendmsg;
	do {
		send(sock,
			&pMsg[sendbytes],
			iTotalsize-sendbytes, 0);
	} while (sendbytes<iTotalsize);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}

int SendMsg(SOCKET sock, PACKET_HEADER ph, char* msg)
{	
	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph = ph;
	memcpy(sendmsg.msg, msg, strlen(msg));
	int sendbytes = 0;
	int iTotalsize = strlen(msg) + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&sendmsg;
	do {
		send(sock,
			&pMsg[sendbytes],
			iTotalsize - sendbytes, 0);
	} while (sendbytes<iTotalsize);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}
int SendMsg(SOCKET sock, UPACKET* uPacket)
{
	
	int sendbytes = 0;
	int iTotalsize = strlen(msg) + PACKET_HEADER_SIZE;
	char* pMsg = (char*)&sendmsg;
	do {
		send(sock,
			&pMsg[sendbytes],
			iTotalsize - sendbytes, 0);
	} while (sendbytes<iTotalsize);
	return sendmsg.ph.len + PACKET_HEADER_SIZE;
}

DWORD WINAPI clientThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	while (1)
	{
		char buffer[256] = { 0, };
		int recvbyte = 0;
		while (1)
		{

			recvbyte += recv(sock, (char*)&buffer[recvbyte],
				sizeof(char) * PACKET_HEADER_SIZE - recvbyte, 0);
			if (recvbyte == PACKET_HEADER_SIZE)
			{
				UPACKET packet;
				ZeroMemory(&packet, sizeof(packet));
				memcpy(packet.ph, buffer, sizeof(char)*PACKET_HEADER_SIZE);
				int rByte == 0;
				do
				{
					rByte += recv(sock,
						(char*)&packet.msg[rByte],
						sizeof(char)*packet.ph.len - rByte, 0);

				} while (packet.ph.len > rByte)
					recvbyte = 0;
				switch (packet.ph.type)
				{
				case PACKET_CHAT_MSG:
				{
					printf("패킷 완성%s", packet.msg);
					SendMsg()
				}break;
				}
			}
	}Sleep(1);
	closesocket(sock);
	return 1;
}


void main()
{
	if (BeginWinSock() == false)
	{
		return;
	}



	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);

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
	ioctlsocket(listenSock, FIONBIO, &on); //FIONBIO 블럭형 X





	int g_iNumUser = 0;

	while (g_iNumUser < 10)
	{


		SOCKADDR_IN clientaddr;
		int addlen = sizeof(clientaddr);
		SOCKET client = accept(listenSock, (sockaddr*)&clientaddr, &addlen);  // 누군가 -> 접속시도
		if (client == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) //WSAEWOULDBLOCK와 같지 않으면 오류
			{
				exit(1);
			}

			// Use inet_ntop() or lnetNtop()
			printf("\nip=%s,port=%d", inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));

			if (client != SOCKET_ERROR)
			{
				HANDLE hThread = CreateThread(0, 0, clientThread, clientaddr, 0, &threadID);
			}
			//char ip[INET_ADDRSTRLEN] = { 0, };
			//char ip[256] = { 0, };
			//printf("\nip=%s,port=%d", inet_ntop(AF_INET, &clientAddr.sin_addr, ip, INET6_ADDRSTRLEN),
			//	ntohs(clientAddr.sin_port));
		}
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