#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
using namespace std;
#pragma comment (lib,"winmm.lib") //timeGetTime 함수 사용하기 위한 선언

extern HWND			g_hWnd;
extern RECT			g_rtClient;
extern int			g_iFPS;//1 초당 프레임 개수
extern float		g_fSecPerFrame; //1프레임의 경과 시간
extern float		g_fAccumulation; // 실행된 경과 시간
