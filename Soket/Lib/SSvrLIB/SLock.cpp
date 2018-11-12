#include "SLock.h"



SLock::SLock(SServerObj* pObj) : m_pSerObj(pObj)
{
	if (pObj == NULL)return;
	EnterCriticalSection(&pObj->m_cs);
}


SLock::~SLock(void)
{
	if (m_pSerObj == NULL)return;
	LeaveCriticalSection(&m_pSerObj->m_cs);
}
