#include "S_DebugString.h"
#include "S_Lock.h"

void S_DebugString::Print(char* fmt, ...)
{
	if (m_hList == NULL)
	{
		return;
	}
	{
		S_Lock Lock(this);
		va_list arg;
		va_start(arg, fmt);
		char buf[MAX_ARRAY] = { 0, };
		vsprintf_s(buf, fmt, arg);
		SendMessage(m_hList, LB_ADDSTRING, 0,
			(LPARAM)S_Debug.GetMbToWcs(buf));
		int iIndex = SendMessage(m_hList, LB_GETCOUNT, 0, 0);
		if (iIndex > 30)
		{
			SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
		}
		va_end(arg);
	}
}

WCHAR* S_DebugString::GetMbToWcs(const char* strMsg)
{
	TCHAR Msg[4096] = { 0, };
	{
		S_Lock Lock(this);
		int iRen = MultiByteToWideChar(CP_ACP, 0, strMsg, -1, 0, 0);

		ConvertAnsiStringToWideCch(Msg, strMsg, iRen);
	}
	return Msg;
}
char* S_DebugString::GetWcsToMbs(const WCHAR* strMsg)
{
	char Msg[4096] = { 0, };
	{
		S_Lock Lock(this);
		int iRen = WideCharToMultiByte(CP_ACP, 0, strMsg, -1, 0, 0, NULL, NULL);
		ConvertWideStringToAnsiCch(Msg, strMsg, iRen);
	}
	return Msg;
}
HRESULT S_DebugString::ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen)
{
	{
		S_Lock Lock(this);
		if (msg == NULL || strMsg == NULL || iRen < 1)
		{
			return E_INVALIDARG;
		}
		int i_Ret = WideCharToMultiByte(CP_ACP, 0, strMsg, -1, msg, iRen, NULL, NULL);
		if (i_Ret == 0)
		{
			return E_FAIL;
		}
		return S_OK;
	}
}

HRESULT S_DebugString::ConvertAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int iRen)
{
	{
		S_Lock Lock(this);
		if (msg == NULL || strMsg == NULL || iRen < 1)
		{
			return E_INVALIDARG;
		}
		int i_Ret = MultiByteToWideChar(CP_ACP, 0, strMsg, -1, msg, iRen);

		if (iRen == 0)
		{
			return E_FAIL;
		}
		msg[iRen - 1] = 0;
	}
	return S_OK;
}

void S_DebugString::S_Error(bool bPrint)
{
	{
		S_Lock Lock(this);
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			char* lpMsgbuf;
			FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
				WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(char*)&lpMsgbuf, 0, NULL);
			if (bPrint)
			{
				MessageBoxA(NULL, lpMsgbuf, "ERROR", MB_OK);
			}
			else
			{
				OutputDebugStringA((char*)lpMsgbuf);
			}
			LocalFree(lpMsgbuf);
		}
	}
}
bool S_DebugString::Init()
{
	m_hList = NULL;
	return true;
}
bool S_DebugString::Release()
{
	return true;
}


S_DebugString::S_DebugString()
{
}


S_DebugString::~S_DebugString()
{
}
