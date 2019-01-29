#ifndef TBASIS_H
#define TBASIS_H
#include "TUtils.h"
#include "TDxHelper.h"


#if defined(DEBUG) || defined(_DEBUG)
	#if defined(WIN64)
		#pragma comment( lib, "TBasisLib64d.lib" )
	#else
		#pragma comment( lib, "TBasisLib32d.lib" )
	#endif
#else
	#if defined(WIN64)
		#pragma comment( lib, "TBasisLib64R.lib" )
	#else
		#pragma comment( lib, "TBasisLib32R.lib" )
	#endif
#endif

namespace TBASIS
{
	//extern float		g_fSecPerFrame;
	extern float		g_fDurationTime;
	extern HWND			g_hWnd;
	extern HINSTANCE	g_hInstance;
	extern UINT			g_iClientWidth;
	extern UINT			g_iClientHeight;
	extern RECT			g_rtClient;
}
using namespace TBASIS;
//////////////////////////////////////////////
// WinMain ∏≈≈©∑Œ
//////////////////////////////////////////////
#define TBASIS_START int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ Sample gSample;
#define TBASIS_WIN(x) if( !gSample.InitWindow( hInstance, nCmdShow,  L#x ) )	{	return 0;	}	ShowCursor ( TRUE );gSample.Run();	return 1; }
#define TBASIS_RUN(x) TBASIS_START; TBASIS_WIN(x);

static TCHAR g_szDataPath[] = L"../../data/";
#endif //TBASIS_H