#pragma once
#include "SServerObj.h"

class SDebugString : public SSingleton<SDebugString>, public SServerObj 
{
private:
	friend class SSingleton<SDebugString>;
public:
	HWND		m_hList; //  ������ �ڵ�
public:
	void		Print(char* fmt, ...); // ��� �Լ�
public:
	bool		Init(); // �ʱ�ȭ
	bool		Release(); // �Ҹ�
	WCHAR*		GetMbToWcs(const char* strMsg); // ��Ƽ����Ʈ�� �����ڵ�� ��ȯ
	char*		GetWcsToMbs(const WCHAR* strMsg); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
	HRESULT		ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
	HRESULT		ConvertAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int iRen); // ��Ƽ����Ʈ�� �����ڵ�� ��ȯ

	void		T_ERROR(bool bPrint = false);
public:
	SDebugString(void);
	virtual ~SDebugString(void);
};
#define I_Debug SDebugString::GetInstance()

