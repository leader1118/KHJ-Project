#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	//exit(-1);
}
void main()
{
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		Error("sock invalid");
	}
	SOCKADDR_IN serveradd;
	ZeroMemory(&serveradd, sizeof(serveradd));
	serveradd.sin_family = AF_INET;
	serveradd.sin_port = htons(10000);
	// ��Ƽ�ɽ�Ʈ �׷쿡 �����Ϸ��� �ݵ�� INADDR_ANY�� ����ؾ� �Ѵ�.
	serveradd.sin_addr.s_addr = htonl(INADDR_ANY);
	int iRet = bind(sock, (SOCKADDR*)&serveradd, sizeof(serveradd));
	if (iRet == SOCKET_ERROR)
	{
		Error("sock invalid");
	}

	// INCLUDE ��� ���� 
	// IP_ADD_SOURCE_MEMBERSHIP <->IP_DROP_SOURCE_MEMBERSHIP
	/*struct ip_mreq_source mreqsrc;
	mreqsrc.imr_interface.s_addr = htonl(INADDR_ANY);
	mreqsrc.imr_multiaddr.s_addr = inet_addr("235.7.8.9");
	mreqsrc.imr_sourceaddr.s_addr = inet_addr("192.168.0.61");
	setsockopt(sock, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char *)&mreqsrc, sizeof(mreqsrc));
	mreqsrc.imr_sourceaddr.s_addr = inet_addr("192.168.0.60");
	setsockopt(sock, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char *)&mreqsrc, sizeof(mreqsrc));
	*/


	// EXCLUDE ��� ����
	// IP_ADD_MEMBERSHIP <-> IP_BLOCK_SOURCE
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr("235.7.8.9");
	mreq.imr_interface.s_addr = inet_addr("192.168.0.101");
	iRet = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (iRet == SOCKET_ERROR)
	{
		Error("sock invalid");
	}
	struct ip_mreq_source mreqsrc;
	mreqsrc.imr_interface = mreq.imr_interface;
	mreqsrc.imr_multiaddr = mreq.imr_multiaddr;
	mreqsrc.imr_sourceaddr.s_addr = inet_addr("192.168.0.33");
	setsockopt(sock, IPPROTO_IP, IP_BLOCK_SOURCE, (char *)&mreqsrc, sizeof(mreqsrc));


	SOCKADDR_IN clientAddr;
	char buf[256] = { 0, };
	int addlen;
	while (1)
	{
		addlen = sizeof(clientAddr);
		iRet = recvfrom(sock, buf, 256, 0, (SOCKADDR*)&clientAddr, &addlen);
		if (iRet == SOCKET_ERROR)
		{
			Error("sock invalid");
		}
		buf[iRet] = 0;
		printf("\n[%s:%d]:%s",
			inet_ntoa(clientAddr.sin_addr),
			ntohs(clientAddr.sin_port),
			buf);
	}
	// �������α׷��� �����ϰų� ������ ������ �׷� ������ ��������.
	setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	WSACleanup();
}