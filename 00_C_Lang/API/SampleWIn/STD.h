#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
using namespace std;
#pragma comment (lib,"winmm.lib") //timeGetTime �Լ� ����ϱ� ���� ����

extern HWND			g_hWnd;
extern RECT			g_rtClient;
extern int			g_iFPS;//1 �ʴ� ������ ����
extern float		g_fSecPerFrame; //1�������� ��� �ð�
extern float		g_fAccumulation; // ����� ��� �ð�
