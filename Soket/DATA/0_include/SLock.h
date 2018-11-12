#pragma once
#include "SServerObj.h"
class SLock // SLock == Synchronize
{
public:
	SServerObj* m_pSerObj;
public:
	SLock(SServerObj* pObj);
	virtual ~SLock(void);
};