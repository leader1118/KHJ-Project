#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <windowsx.h>
#include <process.h>
#include <thread>

#include <iostream>
#include <tchar.h>
#include <string>

#include <algorithm>
#include <io.h>
#include <vector>
#include <list>
#include <map>



#pragma comment (lib,"SSvrLIB.lib")
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#include "SSingleton.h"

extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern int			g_iFPS;// 1�ʴ� ������ ����
extern float		g_fSecPerFrame; // 1�������� ����ð�
