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
					printf("��Ŷ �ϼ�%s", packet.msg);
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
	ioctlsocket(listenSock, FIONBIO, &on); //FIONBIO ���� X





	int g_iNumUser = 0;

	while (g_iNumUser < 10)
	{


		SOCKADDR_IN clientaddr;
		int addlen = sizeof(clientaddr);
		SOCKET client = accept(listenSock, (sockaddr*)&clientaddr, &addlen);  // ������ -> ���ӽõ�
		if (client == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) //WSAEWOULDBLOCK�� ���� ������ ����
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