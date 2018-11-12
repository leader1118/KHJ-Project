#pragma once
#define DIRECTINPUT_VERSION 0x0800
#ifndef UNICODE
#error "TBAIS는 유니코드로 컴파일 해야 합니다."
#endif

#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <crtdbg.h>
#include <cassert>
#include <assert.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <dinput.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <new>
#include <set>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>

using namespace std;

#define SAMPLE_BUFFER_SIZE 16
#define KEYSTATECOUNT		256

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"dwrite.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib,"d3dx10d.lib")
#pragma comment (lib,"d3dx11d.lib")
#pragma comment (lib,"dxgi.lib")
#else
#pragma comment (lib,"d3dx11.lib")
#pragma comment (lib,"d3dx11.lib")
#endif
#pragma comment (lib,"d3dcompiler.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"comctl32.lib")


typedef basic_string<TCHAR>				T_STR;
typedef basic_string<TCHAR>::iterator	T_ITOR;

typedef vector<basic_string<TCHAR>>	T_STR_VECTOR;
typedef vector<string>				C_STR_VECTOR;

typedef list<basic_string<TCHAR>>	T_STR_LIST;
typedef string						CHAR_STRING;

typedef vector<DWORD>				DWORD_VECTOR;
typedef	vector< DWORD >::iterator	DWORD_VECTOR_ITOR;

typedef list<DWORD>					DWORD_LIST;
typedef list<DWORD>::iterator		DWORD_LIST_ITOR;

typedef list< HANDLE >				HANDLE_LIST;
typedef	list< HANDLE >::iterator	HANDLE_LIST_ITOR;

/////////////////////////////////////////////
// 템플릿 객체 릴리즈 함수
/////////////////////////////////////////////

template<class Interface> inline void SAFE_RELEASE(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}
////////////////////////////////////////
// Assert
////////////////////////////////////////

#ifndef Assert
#if defined(_DEBUG) || defined (_DEBUG)
	#define Assert(b)do {if(!(b)){OutputDebugStringW(L"Assert:"#b L"\n");}} while(0)
#else
	#define Assert(b)
#endif //_DEBUG||_DEBUG
#endif


//////////////////////////////////////
// DX 메소드 호출에 대한 반환값 처리 매크로
//////////////////////////////////////

#ifndef V
#define V(x) {hr=(x);}
	#endif
#ifndef V_RETURN
	#define V_RETURN(x){hr=(x); if(FAILED(hr)){return hr;}}
#endif


//////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
//////////////////////////////////////

#ifndef SAFE_ZERO
#define SAFE_ZERO(A){A=0;}
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A,B) {if(!A)A =new B;}
#endif

#ifndef SAFE_DEL
#define SAFE_DEL(A){if(A)delete A; (A)=NULL;}
#endif

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A,B,C) {if(!A&&C)A=newB[C];}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A) {if(A)delete[]A; (A)=NULL;}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A){if(A){(A)->Release(); (A)=NULL;}}
#endif

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR(A,B) {if(!A)A=new B; if(A)memset (A,0,sizeof(B));};
#endif

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR(A,B,C){if(!A && C)A=newB[C]; if(A)memset (A,0,sizeof(B)*C);};
#endif