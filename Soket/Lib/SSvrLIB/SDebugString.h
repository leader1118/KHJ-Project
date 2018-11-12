#pragma once
#include "SServerObj.h"

class SDebugString : public SSingleton<SDebugString>, public SServerObj 
{
private:
	friend class SSingleton<SDebugString>;
public:
	HWND		m_hList; //  윈도우 핸들
public:
	void		Print(char* fmt, ...); // 출력 함수
public:
	bool		Init(); // 초기화
	bool		Release(); // 소멸
	WCHAR*		GetMbToWcs(const char* strMsg); // 멀티바이트를 유니코드로 변환
	char*		GetWcsToMbs(const WCHAR* strMsg); // 유니코드를 멀티바이트로 변환
	HRESULT		ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen); // 유니코드를 멀티바이트로 변환
	HRESULT		ConvertAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int iRen); // 멀티바이트를 유니코드로 변환

	void		T_ERROR(bool bPrint = false);
public:
	SDebugString(void);
	virtual ~SDebugString(void);
};
#define I_Debug SDebugString::GetInstance()

