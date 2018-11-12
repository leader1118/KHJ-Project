#include "SPacket.h"

// 임계영역 , 락 
CRITICAL_SECTION	 g_crit; // 유저모드
HANDLE				 g_hMutex; // 커널 모드 
SOCKET g_allClientSocket[100];
int	   g_iNumClient = 0;

int SendMsg(SOCKET sock, char* msg, WORD type)
{
	SPacket packet(type);
	packet << msg;
	int iRet = send(sock, (char*)&packet.m_uPacket, packet.m_uPacket.ph.len + PACKET_HEADER_SIZE, 0);
	return iRet;
}

void GreetMessage(SOCKET sock)
{
	char message[MAX_PATH] = { 0, };
	sprintf_s(message, "[서버]환영합니다.\n");
	SendMsg(sock, message, PACKET_CHAT_MSG);
	DWORD dwRet = WaitForSingleObject(g_hMutex, INFINITE); // 싱글 대기함수
	g_allClientSocket[g_iNumClient] = sock;
	g_iNumClient++;
	ReleaseMutex(g_hMutex);
	// temp = sock
}

DWORD WINAPI ClientThread(LPVOID arg) // Thread 생성
{
	SOCKET sock = (SOCKET)arg;
	SOCKADDR_IN clientaddr;

	char buffer[256] = { 0, };
	int recvbyte = 0;
	while (1) // 무한반복
	{
		recvbyte += recv(sock, &buffer[recvbyte], sizeof(char)* PACKET_HEADER_SIZE - recvbyte, 0);
		if (recvbyte == 0) break;
		if (recvbyte == PACKET_HEADER_SIZE)
		{
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph, buffer, sizeof(char)*PACKET_HEADER_SIZE);
			int rByte = 0;
			int iRecvByte = 0;
			do
			{
				iRecvByte = recv(sock, (char*)&packet.msg[rByte], sizeof(char)* packet.ph.len - rByte, 0);
				if (iRecvByte == 0)break;
				rByte += iRecvByte;
			} while (packet.ph.len > rByte);

			if (iRecvByte <= 0)break;
			recvbyte = 0;
			switch (packet.ph.type)
			{
			case PACKET_CHAT_MSG:
			{
				printf("패킷 완성 %s", packet.msg);
				//EnterCriticalSection(&g_crit);
				DWORD dwRet = WaitForSingleObject(g_hMutex,INFINITE); // 대기 함수
				if (dwRet != WAIT_TIMEOUT)
				{
					for (int iClient = 0; iClient < g_iNumClient; iClient++)
					{
						int iSendByte = SendMsg(g_allClientSocket[iClient], packet.msg, PACKET_CHAT_MSG);
						if (iSendByte == SOCKET_ERROR)
						{
							printf(" 소켓 오류\n");
							break; // 오류면 클라이언트 종료
						}
					}
				}
				//LeaveCriticalSection(&g_crit);
				ReleaseMutex(g_hMutex);
			}break;
			}
		}
		Sleep(1);
	}

	// 클라이언트 종료 처리
	// EnterCriticalSection(&g_crit);
	WaitForSingleObject(g_hMutex, INFINITE); // 대기함수

	for (int iClient = 0; iClient < g_iNumClient; iClient++)
	{
		if (g_allClientSocket[iClient] == sock)
		{
			for (int iUser = iClient; iUser < g_iNumClient; iUser++)
			{
				g_allClientSocket[iUser] = g_allClientSocket[iUser + 1];
			}
			break;
		}
	}
	g_iNumClient--;
	// LeaveCriticalSection(*g_crit);
	ReleaseMutex(g_hMutex);
	closesocket(sock);
	return 0;
}

// 소켓 생성
// 연결형, TCP프로토콜(SOCK_STREAM, IPPROTO_TCP)
// 비연결형m, UDP프로토콜 (SOCK_DGRAM,IPPROTO_UDP)
int main(int argc, char* argv[])
{
	HANDLE hExecuteMutex = CreateMutex(NULL, FALSE, L"OnceMutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hExecuteMutex);
		return 1;
	}
	InitializeCriticalSection(&g_crit);
	// TRUE = 현재의 스레드가 소유자
	// FALSE = 소유자가 없다. (신호상태) : 비신호 상태

	unsigned short iPort = 10000;  //atoi(argv[1]);
									// 윈도우 소켓 (윈속) 초기화
	WSADATA wsa;
	int iRet;
	HANDLE hThread;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return 1; }
	{
		SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
		{
			SOCKADDR_IN sa;
			ZeroMemory(&sa, sizeof(sa));
			sa.sin_family = AF_INET;
			sa.sin_port = htons(iPort);
			sa.sin_addr.s_addr = htonl(INADDR_ANY);
			// 소켓을 대상 ip에 연결해라.
			iRet = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
			if (iRet == SOCKET_ERROR) return -1;
			iRet = listen(listensock, SOMAXCONN);
			if (iRet == SOCKET_ERROR)return -1;
			SOCKADDR_IN clientaddr;
			SOCKET client;
			while (1)
			{
				int addlen = sizeof(clientaddr);
				client = accept(listensock, (SOCKADDR*)&clientaddr, &addlen);
				printf("클라이언트 접속 : IP:%s,PORT:%d \n",
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				//EnterCriticalSection(&g_crit);
				// 신호상태 일 경우만 진입
				WaitForSingleObject(g_hMutex, INFINITE); // 대기 함수
				GreetMessage(client);
				//LeaveCriticalSection(&g_crit);
				ReleaseMutex(g_hMutex); // 비신호상태로 전환

				DWORD dwRecvThreadID;
				hThread = CreateThread(0, 0, ClientThread, (LPVOID)client, 0, &dwRecvThreadID);
			}
		}
		closesocket(listensock);

	}
	// 윈도우 소켓 소멸
	iRet = WSACleanup();

	DeleteCriticalSection(&g_crit);
	CloseHandle(g_hMutex);
	CloseHandle(hExecuteMutex);
	return 0;
}