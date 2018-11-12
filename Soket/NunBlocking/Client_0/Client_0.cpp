#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32")


#define MAX_BUFFER_SIZE 256

void T_ERR_EXIT(TCHAR* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(TCHAR*)&IpMsgBuf, 0, NULL);
	MessageBox(NULL, (TCHAR*)IpMsgBuf, msg,MB_ICONERROR);
	LocalFree(IpMsgBuf);
}

int NonBlockingSocket(SOCKET sock, u_long iMode)
{
	// 넌블로킹 소켓으로 만들고
	// controls the I/O mode of a socket.

	int iResult = ioctlsocket(sock, FIONBIO, &iMode);
	if (iResult != NIIF_ERROR)
	{
		T_ERR_EXIT(_T("ioctlsocket"));
	}
	return iResult;
}

// 접속시간을 timeout만큼 제한한다.
bool tConnect(SOCKET sock, int timeout)
{
	TIMEVAL Timeout;
	Timeout.tv_sec = timeout;
	Timeout.tv_usec = 0;
	struct sockaddr_in address;
	unsigned long iMode = 1;
	int iResult = ioctlsocket(sock, FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld \n", iResult);
	}

	// 넌블로킹 소켓으로 다시 전환한다.
	iMode = 0;
	iResult = ioctlsocket(sock, FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld \n", iResult);
	}

	fd_set Write, Err;
	FD_ZERO(&Write);
	FD_ZERO(&Err);
	FD_SET(sock, &Write);
	FD_SET(sock, &Err);

	// 넌블로킹 소켓으로 TImeout 만큼 대기한다.
	iResult = select(0, NULL, &Write, &Err, &Timeout);
	if (iResult == 0)
	{
		// timeout
		return true;
	}
	if (FD_ISSET(sock, &Write))
	{
		//Connected!
		return true;
	}
	if (FD_ISSET(sock, &Err))
	{
		//Error
	}
	return false;
}

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);

	if (NonBlockingSocket(Sock, TRUE) == SOCKET_ERROR)return;
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_addr.s_addr = inet_addr("192,168,0,106");
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);

	int iRet = connect(Sock,(SOCKADDR*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			T_ERR_EXIT(_T("connect"));
			return;
		}
		// 접속 시간제한은 WSAEWOULDBLOCK 일경우 세팅한다.
		if (tConnect(Sock, 3000) == false)
		{
			return;
		}
	}
	// 넌블로킹 소켓으로 다시 전환한다.
	if (NonBlockingSocket(Sock, TRUE) == SOCKET_ERROR)return;

	char buf[MAX_BUFFER_SIZE] = { 0, };
	int iEnd = 0;
	while (1)
	{
		if (_kbhit() == 1)
		{
			int iValue = _getch();
			if (strlen(buf) == 0 && iValue == '\r')break;
			if (iValue == '\r')
			{
				if (strlen(buf) == 1)break;
				int iRet = send(Sock, buf, strlen(buf), 0);
				if (iRet == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						T_ERR_EXIT(_T("send"));
						closesocket(Sock);
						break;
					}
				}
				memset(buf, 0, sizeof(char)*MAX_BUFFER_SIZE);
				iEnd = 0;
			}
			else
			{
				if (iEnd < MAX_BUFFER_SIZE - 1)
				{
					buf[iEnd++] = iValue;
				}
			}
		}
		else
		{
			char bufRecv[MAX_BUFFER_SIZE] = { 0, };
			int iRecvByte = recv(Sock, bufRecv, MAX_BUFFER_SIZE - 1, 0);
			if (iRecvByte == 0)break;
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					closesocket(Sock);
					T_ERR_EXIT(_T("recv"));
					break;
				}
			}
			bufRecv[iRecvByte] = 0;
			printf("recv=%s\n", bufRecv);
		}
	}
	closesocket(Sock);
	WSACleanup();
}
