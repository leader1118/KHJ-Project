#pragma once
#define DIRECTINPUT_VERSION 0x800
#include <windows.h> 
#include <assert.h> 
#include <tchar.h> 
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <tchar.h>
#include "d3dx11.h"
#include "dxgi.h" 
#include "d3dcompiler.h"
#include <d3dx10math.h>
#include <wrl.h>
#pragma comment(lib,"d3dx10d.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"3D_lib.lib")

using namespace std;
using namespace Microsoft::WRL;

typedef std::basic_string<char> C_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::basic_string<TCHAR> T_STR;
typedef std::basic_string<char>::iterator C_ITOR;
typedef std::basic_string<wchar_t>::iterator W_ITOR;
typedef std::basic_string<TCHAR>::iterator T_ITOR;

#define GAME_START int WINAPI WinMain(HINSTANCE hInst,	HINSTANCE hPrevInst,LPSTR   lpCmdLine,int   nCmdShow){
#define GAME_END }
#define GAME_RUN(s,w,h) GAME_START{ Sample win;win.SetWindow(hInst, L#s,w,h);win.Run();}GAME_END

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern RECT  g_rtClient;
extern bool g_bActiveApp;
extern float g_fGameTimer;
extern float g_fSecPerFrame;

struct TGameInput
{
	BOOL bFront;
	BOOL bBack;
	BOOL bLeft;
	BOOL bRight;
	BOOL bAttack;
	BOOL bJump;
	BOOL bButton0;
	BOOL bButton1;
	BOOL bButton2;
};
extern TGameInput g_Input;
template<class T> class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};

#ifndef V
#define V(x) { hr = (x);}
#endif

#ifndef V_RETURN
#define V_RETURN(x) { hr = (x); if( FAILED(hr)){return hr;}}
#endif
//////////////////////////////////////////////
// ��ü �� �迭 �Ҵ�� ���� �� �Ҹ� ��ũ��
//////////////////////////////////////////////
#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif