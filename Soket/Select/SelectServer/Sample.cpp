#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h> // InetNtop() . inet_ntop()
#include <iostream>
#include <map>
#include <time.h>

#pragma comment (lib,"ws2_32")
using namespace std;


//
//FD_SET rSet;
//FD_SET wSet;
//
//int main(void)
//{
//	
//
//	while (1)
//	{
//		FD_ZERO(&rSet);
//		FD_ZERO(&wSet);
//		
//	
//
//		
//		// ���� :
//		// ���ŷ ���� - > ���ŷ�Լ� ���� �ذ�.
//		// ��� : �� ���ŷ ���� -> WSAEWOULDBLOCK �ذ�.
//		timeval time;
//		time.tv_sec = 1;
//		time.tv_usec = 0;
//		int iRet = Select(0, &rSet, &wSet, NULL, &time);
//		if (iRet == SOCKET_ERROR) break;
//		if (iRet == 0) {} // timeout
//		else
//		{ }
//	}
//
//}