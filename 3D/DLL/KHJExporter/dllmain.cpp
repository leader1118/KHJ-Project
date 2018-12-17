// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "Header.h"
extern ClassDesc2* GetExportDesc();
HINSTANCE hInstance;
//*.def 생성 -> 외부노출함수리스트
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		hInstance = hModule;
		DisableThreadLibraryCalls(hInstance);
	}break;   
    }
    return TRUE;
}

// 밖으로 공개해야하는 규칙이 있다.
__declspec(dllexport)const TCHAR* LibDescription() // exporter 이름과 버전 
{
	return _T("KHJExporter ver 100");
}
__declspec(dllexport) int LibNumberClasses() // 클래스가 1개이다.
{
	return 1;
}
__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
	switch (i)
	{
	case 0:return GetExportDesc();
	}
	return 0;
}
__declspec(dllexport) int LibVersion() // 버전
{
	return VERSION_3DSMAX;
}

__declspec(dllexport) int LibInitialize() // 초기화
{
	return TRUE;
}
__declspec(dllexport) int LibShutdown()
{
	return TRUE;
}