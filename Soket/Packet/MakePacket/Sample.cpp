#include "SPacket.h"

// �Ӱ迵�� , �� 
CRITICAL_SECTION	 g_crit; // �������
HANDLE				 g_hMutex; // Ŀ�� ��� 
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
	sprintf_s(message, "[����]ȯ���մϴ�.\n");
	SendMsg(sock, message, PACKET_CHAT_MSG);
	DWORD dwRet = WaitForSingleObject(g_hMutex, INFINITE); // �̱� ����Լ�
	g_allClientSocket[g_iNumClient] = sock;
	g_iNumClient++;
	ReleaseMutex(g_hMutex);
	// temp = sock
}

DWORD WINAPI ClientThread(LPVOID arg) // Thread ����
{
	SOCKET sock = (SOCKET)arg;
	SOCKADDR_IN clientaddr;

	char buffer[256] = { 0, };
	int recvbyte = 0;
	while (1) // ���ѹݺ�
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
				printf("��Ŷ �ϼ� %s", packet.msg);
				//EnterCriticalSection(&g_crit);
				DWORD dwRet = WaitForSingleObject(g_hMutex,INFINITE); // ��� �Լ�
				if (dwRet != WAIT_TIMEOUT)
				{
					for (int iClient = 0; iClient < g_iNumClient; iClient++)
					{
						int iSendByte = SendMsg(g_allClientSocket[iClient], packet.msg, PACKET_CHAT_MSG);
						if (iSendByte == SOCKET_ERROR)
						{
							printf(" ���� ����\n");
							break; // ������ Ŭ���̾�Ʈ ����
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

	// Ŭ���̾�Ʈ ���� ó��
	// EnterCriticalSection(&g_crit);
	WaitForSingleObject(g_hMutex, INFINITE); // ����Լ�

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

// ���� ����
// ������, TCP��������(SOCK_STREAM, IPPROTO_TCP)
// �񿬰���m, UDP�������� (SOCK_DGRAM,IPPROTO_UDP)
int main(int argc, char* argv[])
{
	HANDLE hExecuteMutex = CreateMutex(NULL, FALSE, L"OnceMutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hExecuteMutex);
		return 1;
	}
	InitializeCriticalSection(&g_crit);
	// TRUE = ������ �����尡 ������
	// FALSE = �����ڰ� ����. (��ȣ����) : ���ȣ ����

	unsigned short iPort = 10000;  //atoi(argv[1]);
									// ������ ���� (����) �ʱ�ȭ
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
			// ������ ��� ip�� �����ض�.
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
				printf("Ŭ���̾�Ʈ ���� : IP:%s,PORT:%d \n",
					inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

				//EnterCriticalSection(&g_crit);
				// ��ȣ���� �� ��츸 ����
				WaitForSingleObject(g_hMutex, INFINITE); // ��� �Լ�
				GreetMessage(client);
				//LeaveCriticalSection(&g_crit);
				ReleaseMutex(g_hMutex); // ���ȣ���·� ��ȯ

				DWORD dwRecvThreadID;
				hThread = CreateThread(0, 0, ClientThread, (LPVOID)client, 0, &dwRecvThreadID);
			}
		}
		closesocket(listensock);

	}
	// ������ ���� �Ҹ�
	iRet = WSACleanup();

	DeleteCriticalSection(&g_crit);
	CloseHandle(g_hMutex);
	CloseHandle(hExecuteMutex);
	return 0;
}