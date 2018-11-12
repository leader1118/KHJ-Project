#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

std::vector<SOCKET>g_userList;

int main()
{
	// WSA는 윈속 없으면 유닉스
	// 윈속 초기화
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)	// 0 성공 1실패
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
	addr.sin_addr.s_addr = inet_addr("192.168.0.106");
	addr.sin_port = htons(10000); // string에서 수치로 변환


	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		return 1;
	}

	// 정보를 듣겠다.
	int ret1 = listen(sock, SOMAXCONN);
	if (ret1 = SOCKET_ERROR)
	{
		return 1;
	}

	SOCKET clientSock;
	SOCKADDR_IN clientInfo;
	int		addlen = sizeof(clientInfo);
	char buffer[] = "안녕!";
	while (1)
	{
		clientSock = accept(sock, (sockaddr*)&clientInfo, &addlen); //sock에는 클라이언트의 정보가 들어가 있다

		if (clientSock == INVALID_SOCKET)
		{
			break;
		}
		printf("\n%s,%d", inet_ntoa(clientInfo.sin_addr), // 32비트라는 수치를 string으로 변환
			ntohs(clientInfo.sin_port));

		g_userList.push_back(clientSock);

		while (1)
		{
			send(clientSock, buffer, sizeof(buffer), 0);

			char buffer2[256] = { 0 };
			ret = recv(clientSock, buffer2, sizeof(buffer2), 0);
			if (ret == 0)
			{
				printf("\n정상 종료%s,%d 나갔습니다.",
					inet_ntoa(clientInfo.sin_addr),
					ntohs(clientInfo.sin_port));
				break;
			}
			if (ret<0)
			{
				printf("\n비정상종료 %s,%d 나갔습니다.",
					inet_ntoa(clientInfo.sin_addr),
					ntohs(clientInfo.sin_port));
				break;
			}
			printf("\n정상 종료[%s]%s,%d 받았습니다.",
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

	
	// 윈속 닫기
	WSACleanup();

	std::cout << "HELLO World!\n";
}