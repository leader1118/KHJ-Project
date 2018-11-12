#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib,"ws2_32")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE 512

// 소켓 정보 저장을 위한 구조체와 변수
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE + 1]; // NULL 문자가 포함되기떄문에 +1을 해준다.
	int recvbytes;
	int sendbytes;
};

int iTotalSockets = 0; // SOCKETINFO 구조체의 개수다 . 소켓을 생성할 때마다 1씩 증가하고 소켓을 닫을 때마다 1씩 감소한다.
SOCKETINFO* SocketInfoArray[FD_SETSIZE]; // SOCKETINFO형 포인터를 저장할 배열이다. 원소 개수는 Select 모델에서 처리할 수 있는 소켓의 최대 개수 (FD_SETSIZE)로 정의 하고 있다 // FD_SETSIZE == 64개

// 소켓 관리 함수
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int iIndex);

// 오류 출력 함수
void err_quit(const char* msg);
void err_display(const char* msg);

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 윈속 초기화
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

	// 넌 블로킹 소켓으로 전환
	u_long on = 1;
	retval = ioctlsocket(listen_sock, FIONBIO, &on);
	if (retval == SOCKET_ERROR)
	{
		err_display("ioctlsocket()");
	}

	// 데이터 통신에 사용할 변수
	FD_SET rset, wset;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen, i;

	while (1)
	{
		// 소켓 셋 초기화
		FD_ZERO(&rset);				//
		FD_ZERO(&wset);				// 읽기 셋과 쓰기 셋을 비운 후 연결 대기 소켓을 읽기 셋에 넣는다.
		FD_SET(listen_sock, &rset); //
		for (i = 0; i < iTotalSockets; i++) // 소켓 정보 구조체를 참조하여 모든 소켓을 읽기 또는 쓰기 셋에 넣는다. 받은 데이터가 보낸 데이터보다 많으면 쓰기 셋에, 그렇지 않으면 읽기 셋에 넣는다.
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
		retval = select(0, &rset, &wset, NULL, NULL); // Select 함수 호출 // 예외 셋은 사용하지 않으므로 NULL값을 넣는다. 타임아웃 역시 NULL값을 사용함으로써 조건이 만족될 때까지 무한히 대기하게 한다.
		if (retval == SOCKET_ERROR)
		{
			err_quit("select()");
		}

		// 소켓 셋 검사(1): 클라이언트 접속 수용

		if (FD_ISSET(listen_sock, &rset)) // Select 함수가 리턴하면 먼저 읽기 셋을 검사하여 접속한 클라이언트가 있는지 확인한다. 연결 대기 소켓이 읽기 셋에 있다면 접속한 클라이언트가 있다는 뜻이다.
		{
			addrlen = sizeof(clientaddr);
			client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) // 함수를 호출한 후 리턴 값을 확인하여 오류를 처리한다.
			{
				err_display("accept()");
			}
			else
			{
				printf("\n [TCP 서버] 클라이언트 접속: IP주소 =%s, 포트번호 =%d\n", //접속한 클라이언트 정보를 화면에 출력한다.
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				// 소켓 정보 추가
				AddSocketInfo(client_sock); // ㅎ마수를 호출해 소켓 정보를 추가한다.
			}
		}

		// 소켓 셋 검사(2): 데이터 통신
		for (i = 0; i < iTotalSockets; i++) // 조건을 만족하는 소켓의 개수를 리턴하지만 구체적으로 어떤 소켓인지는 알려주지 않는다. 
		{									//따라서 응용 프로그램이 관리하고 있는 모든 소켓에 대해 소켓 셋에 들어 있는지 여부를 일일이 확인해야한다.
			SOCKETINFO* ptr = SocketInfoArray[i];
			if (FD_ISSET(ptr->sock, &rset)) // 소켓이 읽기 셋에 들어 있다면 recv()함수를 호출한 후 리턴 값을 확인히여 오류를 처리한다.
			{								
				// 데이터 받기
				retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
				if (retval == SOCKET_ERROR) // 오류 발생 또는 정상 종료 모두 RemoveSocketInfo 함수를 호출하여 소켓을 닫고 소켓 정보를 제거한다.
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
				ptr->recvbytes = retval; // 함수 호출이 성공 했으면, 받은 바이트 수(recvbytes)를 갱신한 후 화면에 출력한다.
				// 받은 데이터 출력
				addrlen = sizeof(clientaddr);
				getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
				ptr->buf[retval] = '\0';
				printf("[TCP / %s:%d] %s \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
			}
			if (FD_ISSET(ptr->sock, &wset))  // 소켓이 쓰기 셋에 들어 있다면 send() 함수를 호출한 후 리턴 값을 확인하여 오류를 처리 한다.
			{
				// 데이터 보내기
				retval = send(ptr->sock, ptr->buf + ptr->sendbytes, ptr->recvbytes - ptr->sendbytes, 0);
				if (retval == SOCKET_ERROR) // 오류 발생하면 RemoveSocketInfo를 호출하여 소켓을 닫고 소켓 정보를 제거한다.
				{
					err_display("send()");
					RemoveSocketInfo(i);
					continue;
				}
				ptr->sendbytes += retval; //send 함수 호출이 성공했으면, 보낸 바이트 수(sendbytes)를 갱신
				if (ptr->recvbytes == ptr->sendbytes) // 받은 데이터를 모두 보냈으면, 받은 바이트 수와 보낸 바이트 수를 0으로 초기화한다.
				{
					ptr->recvbytes = ptr->sendbytes = 0;
				}
			}
		}
	}
	// 윈속 종료
	WSACleanup();
	return 0;
}

// 소켓 정보 추가
BOOL AddSocketInfo(SOCKET sock)
{
	if (iTotalSockets >= FD_SETSIZE)
	{
		printf("[오류] 소켓정보를 추가할 수 없습니다.!\n");
		return FALSE;
	}
	SOCKETINFO* ptr = new SOCKETINFO;
	if (ptr == NULL)
	{
		printf("[오류] 메모리가 부족합니다!\n");
		return FALSE;
	}
	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	SocketInfoArray[iTotalSockets] = ptr;

	return TRUE;
}

// 소켓 정보 삭제 
void RemoveSocketInfo(int iIndex)
{
	SOCKETINFO* ptr = SocketInfoArray[iIndex];

	// 클라이언트 정보 얻기
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
	printf("[TCP 서버] 클라이언트 종료: IP주소=%s , 포트 번호 = %d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(ptr->sock);
	delete ptr;

	if (iIndex != (iTotalSockets - 1))
	{
		SocketInfoArray[iIndex] = SocketInfoArray[iTotalSockets - 1];
	}
	--iTotalSockets;
}

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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