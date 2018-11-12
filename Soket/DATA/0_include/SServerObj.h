#pragma once
#include "SvrStd.h"
class SServerObj
{
public:
	CRITICAL_SECTION	m_cs; // 임계 영역,
public:
	SServerObj(void);
	virtual ~SServerObj(void);
};

