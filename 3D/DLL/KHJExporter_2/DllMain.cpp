#include "Header.h"

extern ClassDesc2* GetExportDesc();

HINSTANCE hInstance;
int controlsInit = FALSE;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID/*lpvReserved*/)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
	}
	return TRUE;
}

__declspec(dllexport) const TCHAR* LibDescription()
{
	return _T("KHJUtilExporter 100");
}

__declspec(dllexport) int LibNumberClasses()
{
	return 1;
}

__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
	switch (i) {
	case 0: return GetExportDesc();
	default: return 0;
	}
}

__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec(dllexport) int LibInitialize(void)
{
#pragma message(TODO("Perform initialization here."))
	return TRUE;
}

__declspec(dllexport) int LibShutdown(void)
{
#pragma message(TODO("Perform un-initialization here."))
	return TRUE;
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, _countof(buf)) ? buf : NULL;
	return NULL;
}


