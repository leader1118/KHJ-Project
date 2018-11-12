#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib,"ws2_32")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE 512

// ���� ���� ������ ���� ����ü�� ����
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE + 1]; // NULL ���ڰ� ���ԵǱ⋚���� +1�� ���ش�.
	int recvbytes;
	int sendbytes;
};

int iTotalSockets = 0; // SOCKETINFO ����ü�� ������ . ������ ������ ������ 1�� �����ϰ� ������ ���� ������ 1�� �����Ѵ�.
SOCKETINFO* SocketInfoArray[FD_SETSIZE]; // SOCKETINFO�� �����͸� ������ �迭�̴�. ���� ������ Select �𵨿��� ó���� �� �ִ� ������ �ִ� ���� (FD_SETSIZE)�� ���� �ϰ� �ִ� // FD_SETSIZE == 64��

// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int iIndex);

// ���� ��� �Լ�
void err_quit(const char* msg);
void err_display(const char* msg);

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� �ʱ�ȭ
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		err_quit("socket()");
	}

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1"); loofbackip //inet)addr("192.168.0.106");
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
	{
		err_quit("bind()");
	}

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
	}

	// �� ���ŷ �������� ��ȯ
	u_long on = 1;
	retval = ioctlsocket(listen_sock, FIONBIO, &on);
	if (retval == SOCKET_ERROR)
	{
		err_display("ioctlsocket()");
	}

	// ������ ��ſ� ����� ����
	FD_SET rset, wset;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen, i;

	while (1)
	{
		// ���� �� �ʱ�ȭ
		FD_ZERO(&rset);				//
		FD_ZERO(&wset);				// �б� �°� ���� ���� ��� �� ���� ��� ������ �б� �¿� �ִ´�.
		FD_SET(listen_sock, &rset); //
		for (i = 0; i < iTotalSockets; i++) // ���� ���� ����ü�� �����Ͽ� ��� ������ �б� �Ǵ� ���� �¿� �ִ´�. ���� �����Ͱ� ���� �����ͺ��� ������ ���� �¿�, �׷��� ������ �б� �¿� �ִ´�.
		{
			if (SocketInfoArray[i]->recvbytes > SocketInfoArray[i]->sendbytes)
			{
				FD_SET(SocketInfoArray[i]->sock, &wset);
			}
			else
			{
				FD_SET(SocketInfoArray[i]->sock, &rset);
			}
		}

		// select()
		retval = select(0, &rset, &wset, NULL, NULL); // Select �Լ� ȣ�� // ���� ���� ������� �����Ƿ� NULL���� �ִ´�. Ÿ�Ӿƿ� ���� NULL���� ��������ν� ������ ������ ������ ������ ����ϰ� �Ѵ�.
		if (retval == SOCKET_ERROR)
		{
			err_quit("select()");
		}

		// ���� �� �˻�(1): Ŭ���̾�Ʈ ���� ����

		if (FD_ISSET(listen_sock, &rset)) // Select �Լ��� �����ϸ� ���� �б� ���� �˻��Ͽ� ������ Ŭ���̾�Ʈ�� �ִ��� Ȯ���Ѵ�. ���� ��� ������ �б� �¿� �ִٸ� ������ Ŭ���̾�Ʈ�� �ִٴ� ���̴�.
		{
			addrlen = sizeof(clientaddr);
			client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) // �Լ��� ȣ���� �� ���� ���� Ȯ���Ͽ� ������ ó���Ѵ�.
			{
				err_display("accept()");
			}
			else
			{
				printf("\n [TCP ����] Ŭ���̾�Ʈ ����: IP�ּ� =%s, ��Ʈ��ȣ =%d\n", //������ Ŭ���̾�Ʈ ������ ȭ�鿡 ����Ѵ�.
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				// ���� ���� �߰�
				AddSocketInfo(client_sock); // �������� ȣ���� ���� ������ �߰��Ѵ�.
			}
		}

		// ���� �� �˻�(2): ������ ���
		for (i = 0; i < iTotalSockets; i++) // ������ �����ϴ� ������ ������ ���������� ��ü������ � ���������� �˷����� �ʴ´�. 
		{									//���� ���� ���α׷��� �����ϰ� �ִ� ��� ���Ͽ� ���� ���� �¿� ��� �ִ��� ���θ� ������ Ȯ���ؾ��Ѵ�.
			SOCKETINFO* ptr = SocketInfoArray[i];
			if (FD_ISSET(ptr->sock, &rset)) // ������ �б� �¿� ��� �ִٸ� recv()�Լ��� ȣ���� �� ���� ���� Ȯ������ ������ ó���Ѵ�.
			{								
				// ������ �ޱ�
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
				if (retval == SOCKET_ERROR) // ���� �߻� �Ǵ� ���� ���� ��� RemoveSocketInfo �Լ��� ȣ���Ͽ� ������ �ݰ� ���� ������ �����Ѵ�.
				{
					err_display("recv()");
					RemoveSocketInfo(i);
					continue;
				}
				else if (retval == 0)
				{
					RemoveSocketInfo(i);
					continue;
				}
				ptr->recvbytes = retval; // �Լ� ȣ���� ���� ������, ���� ����Ʈ ��(recvbytes)�� ������ �� ȭ�鿡 ����Ѵ�.
				// ���� ������ ���
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
				ptr->buf[retval] = '\0';
				printf("[TCP / %s:%d] %s \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
			}
			if (FD_ISSET(ptr->sock, &wset))  // ������ ���� �¿� ��� �ִٸ� send() �Լ��� ȣ���� �� ���� ���� Ȯ���Ͽ� ������ ó�� �Ѵ�.
			{
				// ������ ������
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR) // ���� �߻��ϸ� RemoveSocketInfo�� ȣ���Ͽ� ������ �ݰ� ���� ������ �����Ѵ�.
				{
					err_display("send()");
					RemoveSocketInfo(i);
					continue;
				}
				ptr->sendbytes += retval; //send �Լ� ȣ���� ����������, ���� ����Ʈ ��(sendbytes)�� ����
				if (ptr->recvbytes == ptr->sendbytes) // ���� �����͸� ��� ��������, ���� ����Ʈ ���� ���� ����Ʈ ���� 0���� �ʱ�ȭ�Ѵ�.
				{
					ptr->recvbytes = ptr->sendbytes = 0;
				}
			}
		}
	}
	// ���� ����
	WSACleanup();
	return 0;
}

// ���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	if (iTotalSockets >= FD_SETSIZE)
	{
		printf("[����] ���������� �߰��� �� �����ϴ�.!\n");
		return FALSE;
	}
	SOCKETINFO* ptr = new SOCKETINFO;
	if (ptr == NULL)
	{
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return FALSE;
	}
	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[iTotalSockets] = ptr;

	return TRUE;
}

// ���� ���� ���� 
void RemoveSocketInfo(int iIndex)
{
	SOCKETINFO* ptr = SocketInfoArray[iIndex];

	// Ŭ���̾�Ʈ ���� ���
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s , ��Ʈ ��ȣ = %d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(ptr->sock);
	delete ptr;

	if (iIndex != (iTotalSockets - 1))
	{
		SocketInfoArray[iIndex] = SocketInfoArray[iTotalSockets - 1];
	}
	--iTotalSockets;
}

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (LPCSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}