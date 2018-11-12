#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include "TProtocol.h"
#pragma comment(lib,"ws2_32.lib")
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
	do
	{
		sendbytes += send(sock,
			&pMsg[sendbytes],
			iTotalsize - sendbytes, 0);
	} while (sendbytes < iTotalsize);
	return iTotalsize;
}
int main()
{
	// WSA는 윈속 없으면 유닉스
	// 윈속 초기화
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)	// 0 성공 1이 실패
	{
		return 1;
	}

	////////////////////////////////

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); //SOCK_DGRAM // 3번째 인자는 그냥 무조건 0으로 쓰자 // (IPPROTO_TCP,IPPROTO_UDP) 원래는 맞게끔 넣어줘야함
												   //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
												   //SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock == INVALID_SOCKET)
	{
		return 1;
	}
	// 소켓 생성
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET; // 무조건 고정
	addr.sin_addr.s_addr = inet_addr("192.168.0.101"); // 127.0.0.1 loofback 주소
	addr.sin_port = htons(10000);

	// 접속(전화를 걸었다)
	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr)); // 서버의 정보가 들어가 있다
	if (ret == SOCKET_ERROR)
	{
		return 1;
	}
	// SOCKET_ERROR 가 아니면 연결이 된것


	//while (1)
	//{

	//}
	//while (1)99
	//{
	

	/*char buffer3[256] = { 0, };
	recv(sock, buffer3, sizeof(buffer3), 0);
	std::cout << buffer3;*/
	while (1)
	{
		char buffer2[] = { 0, };
		scanf("%s", buffer2);
		send(sock, buffer2, sizeof(buffer2), 0);
	}
	//}

	char buffer[256] = { 0, };
	recv(sock, buffer, sizeof(buffer), 0);
	std::cout << buffer;

	closesocket(sock);
	// 윈속 닫기
	WSACleanup();

	std::cout << "HELLO World!\n";
}