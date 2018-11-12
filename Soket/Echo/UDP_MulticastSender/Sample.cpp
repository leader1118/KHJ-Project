#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

void Error(char* msg)
{
	LPVOID lpMsgBuffer;
	int iError = WSAGetLastError();
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		iError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuffer,
		0, NULL);
	printf("%s", lpMsgBuffer);
	LocalFree(lpMsgBuffer);
	exit(-1);
}
void main()
{
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		return;
	}
	SOCKET SendSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (SendSock == INVALID_SOCKET)
	{
		Error("sock invalid");
	}

	int mulTTL = 64;// 기본값 128
	setsockopt(SendSock, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&mulTTL, sizeof(mulTTL));
	// 전송할 인터페이스 지정 : 기본 라우터 테이블 첫번째 인터페이스가 된다.
	ULONG localif = inet_addr("192.168.0.101");
	setsockopt(SendSock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localif, sizeof(localif));

	//전송시는 그룹에 가입하지 않아도 된다.
	SOCKADDR_IN serveradd;
	ZeroMemory(&serveradd, sizeof(serveradd));
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(10000);
	serveradd.sin_addr.s_addr = inet_addr("235.7.8.9");

	SOCKADDR_IN clientAddr;
	char buf[256] = { 0, };
	char recvbuf[256] = { 0, };
	int addlen;
	int iCount = 0;
	while (1)
	{
		sprintf(buf, "%s:%d", "kgca", iCount++);
		int iRet = sendto(SendSock, buf, strlen(buf), 0, (SOCKADDR*)&serveradd, sizeof(serveradd));
		if (iRet == SOCKET_ERROR)
		{
			Error("sock invalid");
		}
		Sleep(1000);
	}
	WSACleanup();
}