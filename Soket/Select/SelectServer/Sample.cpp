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
//		// 장점 :
//		// 블로킹 소켓 - > 블록킹함수 문제 해결.
//		// 취소 : 넌 블록킹 소켓 -> WSAEWOULDBLOCK 해결.
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