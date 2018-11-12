#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

std::vector<SOCKET>g_userList;

int main()
{
	// WSA�� ���� ������ ���н�
	// ���� �ʱ�ȭ
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)	// 0 ���� 1����
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
	addr.sin_addr.s_addr = inet_addr("192.168.0.106");
	addr.sin_port = htons(10000); // string���� ��ġ�� ��ȯ


	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return 1;
	}

	// ������ ��ڴ�.
	int ret1 = listen(sock, SOMAXCONN);
	if (ret1 = SOCKET_ERROR)
	{
		return 1;
	}

	SOCKET clientSock;
	SOCKADDR_IN clientInfo;
	int		addlen = sizeof(clientInfo);
	char buffer[] = "�ȳ�!";
	while (1)
	{
		clientSock = accept(sock, (sockaddr*)&clientInfo, &addlen); //sock���� Ŭ���̾�Ʈ�� ������ �� �ִ�

		if (clientSock == INVALID_SOCKET)
		{
			break;
		}
		printf("\n%s,%d", inet_ntoa(clientInfo.sin_addr), // 32��Ʈ��� ��ġ�� string���� ��ȯ
			ntohs(clientInfo.sin_port));

		g_userList.push_back(clientSock);

		while (1)
		{
			send(clientSock, buffer, sizeof(buffer), 0);

			char buffer2[256] = { 0 };
			ret = recv(clientSock, buffer2, sizeof(buffer2), 0);
			if (ret == 0)
			{
				printf("\n���� ����%s,%d �������ϴ�.",
					inet_ntoa(clientInfo.sin_addr),
					ntohs(clientInfo.sin_port));
				break;
			}
			if (ret<0)
			{
				printf("\n���������� %s,%d �������ϴ�.",
					inet_ntoa(clientInfo.sin_addr),
					ntohs(clientInfo.sin_port));
				break;
			}
			printf("\n���� ����[%s]%s,%d �޾ҽ��ϴ�.",
				buffer2,
				inet_ntoa(clientInfo.sin_addr),
				ntohs(clientInfo.sin_port));

			std::cout << buffer2;

			for (int iUser = 0; iUser < g_userList.size(); iUser++)
			{
				send(g_userList[iUser], buffer2, sizeof(buffer2), 0);
			}
		}
		//closesocket(clientSock);
	}
	//closesocket(sock);

	
	// ���� �ݱ�
	WSACleanup();

	std::cout << "HELLO World!\n";
}