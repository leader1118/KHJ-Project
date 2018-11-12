#pragma once
#include <windows.h>
#include <assert.h>

#define GAME_START  int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   IpCmdLine, int  nCmdShow){
#define GAME_END  }
#define GAME_RUN(s,w,h) GAME_START{Window win;win.SetWindow(hInst,L#s); win.Run();}GAME_END