#include "SDebugString.h"
#include "SLock.h" // == Synchronize
bool	SDebugString::Init() // 초기화
{
	m_hList = NULL;
	return true;
}
bool	SDebugString::Release() // 소멸 
{
	return true;
}
void	SDebugString::Print(char* fmt, ...) // 출력
{
	if (m_hList == NULL)return; // 리스트가 NULL일경우 return
	{
		SLock Lock(this);
		va_list arg;
		va_start(arg, fmt);
		char buf[256] = { 0, };
		vsprintf_s(buf, fmt, arg);
		SendMessage(m_hList,LB_ADDSTRING,0, // LB_ADDSTRING == 문자열 항목을 추가하여 그 인덱스를 리턴한다. -> LPARAM(포인터사용)
			(LPARAM)I_Debug.GetMbToWcs(buf)); // LPARAM == LONG_PTR
		int index = SendMessage(m_hList, LB_GETCOUNT, 0, 0); // LB_GETCOUNT == 총 항목 개수를 조사한다.
		if (index > 30)
		{
			SendMessage(m_hList, LB_RESETCONTENT,0,0);
		}
		va_end(arg);
	}
}

void SDebugString::T_ERROR(bool bPrint)
{
	SLock Lock(this);
	if (WSAGetLastError() != WSA_IO_PENDING)
	{
		char * IpMsgBuf;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&IpMsgBuf, 0, NULL);
		if (bPrint)
		{
			MessageBoxA(NULL, IpMsgBuf, "ERROR", MB_OK);
		}
		else
		{
			OutputDebugStringA((char*)IpMsgBuf);
		}
		LocalFree(IpMsgBuf);
	}
}

WCHAR* SDebugString::GetMbToWcs(const char* strMsg)
{
	TCHAR msg[4096] = { 0, };
	{
		SLock lock(this);
		int nRen = MultiByteToWideChar(CP_ACP, 0, strMsg, 
										-1, 0, 0);
		ConvertAnsiStringToWideCch(msg, strMsg, nRen);
	}
	return msg;
}

HRESULT SDebugString::ConvertAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int nRen)
{
	{
		SLock lock(this);
		if (msg == NULL || strMsg == NULL || nRen < 1)
		{
			return E_INVALIDARG;
		}
		int nRetrun = MultiByteToWideChar(CP_ACP, 0, strMsg, -1, msg, nRen);
		if (nRen == 0)return E_FAIL;
		msg[nRen - 1] = 0;
	}
	return S_OK;
}

char* SDebugString::GetWcsToMbs(const WCHAR* strMsg)
{
	char msg[4096] = { 0, };
	{
		SLock lock(this);
		int iRen = WideCharToMultiByte(CP_ACP, 0, strMsg, -1, 0, 0, NULL, NULL);
		ConvertWideStringToAnsiCch(msg, strMsg, iRen);
	}
	return msg;
}

HRESULT SDebugString::ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen)
{
	{
		SLock lock(this);
		if (msg == NULL || strMsg == NULL || iRen < 1)
		{
			return E_INVALIDARG;
		}
		int iReturn = WideCharToMultiByte(CP_ACP, 0, strMsg, -1, msg, iRen, NULL, NULL);
		if (iReturn == 0)return E_FAIL;
	}
	return S_OK;
}
SDebugString::SDebugString(void)
{
}


SDebugString::~SDebugString(void)
{
}
