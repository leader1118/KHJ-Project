#include "S_Lock.h"



S_Lock::S_Lock(S_SvrObj* pSvrObj) : m_pSvrObj(pSvrObj)
{
	if (pSvrObj == NULL)
	{
		return;
	}
	EnterCriticalSection(&pSvrObj->m_Ct);
}


S_Lock::~S_Lock()
{
	if (m_pSvrObj == NULL)
	{
		return;
	}
	LeaveCriticalSection(&m_pSvrObj->m_Ct);
}
