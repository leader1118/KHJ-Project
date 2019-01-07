#pragma once
#define DIRECTINPUT_VERSION 0x800

#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <iostream>
#include <string>

#include <map>
#include <list>
#include <vector>
#include <algorithm>

#include "D3DX11.h"
#include "dxgi.h"
#include "d3dcompiler.h"
#include <d3dx10math.h>
#include <wrl.h>

#pragma comment(lib,"d3dx10d.lib")
#pragma commetn(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"3D_LIB_1.lib")

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
extern RECT g_rtClient;
extern bool g_bActiveApp;
extern float g_fGameTimer;
extern float g_fSecPerFrame;

struct SGameInput
{
	BOOL bFront; // w
	BOOL bBack; // s
	BOOL bLeft; // a
	BOOL bRight; // d
	BOOL bButton0; // 마우스 왼쪽 버튼
	BOOL bButton1; // 마우스 휠 버튼
	BOOL bButton2; // 마우스 오른쪽 버튼
};
extern SGameInput g_Input;
template<class S>class SSingleton
{
public:
	static S& GetInstance()
	{
		static S theSingleInstance;
		return theSingleInstance;
	}
};




///////////////////// 매크로 //////////////////////
#define randf(x)   (x*rand()/(float)RAND_MAX)
#define randf2(x,off)   (off+(x*rand())/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x, minX, maxX) if(x>maxX) x= maxX;else if(x< minX) x= minX;

#ifndef V
#define V(x) { hr = (x);}
#endif

#ifndef V_RETURN
#define V_RETURN(x) { hr = (x); if( FAILED(hr)){return hr;}}
#endif
//////////////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
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