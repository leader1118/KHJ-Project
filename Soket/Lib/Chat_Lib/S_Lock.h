#pragma once
#include "S_SvrObj.h"

class S_Lock
{
public:
	S_SvrObj* m_pSvrObj;
public:
	S_Lock(S_SvrObj* pSvrObj);
	virtual ~S_Lock();
};

