#pragma once
#include "S_SvrObj.h"
class S_DebugString : public S_SvrObj,public Singleton<S_DebugString>
{
private:
	friend class Singleton<S_DebugString>;
public:
	HWND m_hList;
public:
	void		Print(char* fmt, ...);
	bool		Init();
	bool		Release();
	WCHAR*		GetMbToWcs(const char* strMsg);
	char*		GetWcsToMbs(const WCHAR* strMsg);
	HRESULT		ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen);
	HRESULT		ConvertAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int iRen);
	void		S_Error(bool bprint = false);
public:
	S_DebugString();
	virtual ~S_DebugString();
};
#define S_Debug S_DebugString::GetInstance()

