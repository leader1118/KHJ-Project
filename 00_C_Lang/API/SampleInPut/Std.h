#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>

#pragma comment(lib, "winmm.lib")

#define GAME_START int WINAPI WinMain(HINSTANCE hInst,	HINSTANCE hPrevInst,LPSTR   lpCmdLine,int   nCmdShow){
#define GAME_END }
#define GAME_RUN(s,w,h) GAME_START{ Sample win;win.SetWindow(hInst, L#s,w,h);win.Run();}GAME_END

extern HWND g_hWnd;

template<class T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};