#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <thread>
#include <process.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <functional>

#include <vector>
#include <list>
#include <string>

using namespace std;

#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"winmm.lib")

#pragma comment (lib,"Chat_Lib.lib")

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char> C_STR;

#include "S_header.h"