#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winmm.lib")

DWORD WINAPI SendThread(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	while (1)
	{
		char buffer[256] = { 0, };
		fgets(buffer, 256, stdin);
		if (strlen(buffer) <=1)
		{
			break;
		}
		send(sock,buffer,strlen(buffer),0);
	}
	return true;
}

int main()
{
	// WSA�� ���� ������ ���н�
	// ���� �ʱ�ȭ
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)	// 0 ���� 1�� ����
	{
		return 1;
	}

	////////////////////////////////

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); //SOCK_DGRAM // 3��° ���ڴ� �׳� ������ 0���� ���� // (IPPROTO_TCP,IPPROTO_UDP) ������ �°Բ� �־������
												   //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
												   //SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock == INVALID_SOCKET)
	{
		return 1;
	}
	// ���� ����
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET; // ������ ����
	addr.sin_addr.s_addr = inet_addr("192.168.0.27"); // 127.0.0.1 loofback �ּ�
	addr.sin_port = htons(10000);

	// ����(��ȭ�� �ɾ���)
	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr)); // ������ ������ �� �ִ�
	if (ret == SOCKET_ERROR)
	{
		return 1;
	}
	// SOCKET_ERROR �� �ƴϸ� ������ �Ȱ�


	//while (1)
	//{

	//}
	//while (1)99
	//{
	DWORD id;
	HANDLE hThread = CreateThread(NULL, 0,SendThread,(LPVOID)sock,0,&id);
	while (1)
	{
		char buffer3[256] = { 0, };
		int iRet=recv(sock, buffer3, sizeof(buffer3), 0);
		if (iRet == 0)break;
		if (iRet == SOCKET_ERROR)break;
		std::cout << buffer3;
	}
	
	char buffer2[] = { 0, };
	scanf("%s", buffer2);
	send(sock, buffer2, sizeof(buffer2), 0);
	
	//}

	/*char buffer[256] = { 0, };
	recv(sock, buffer, sizeof(buffer), 0);
	std::cout << buffer;*/

	closesocket(sock);
	// ���� �ݱ�
	WSACleanup();

	std::cout << "HELLO World!\n";
}