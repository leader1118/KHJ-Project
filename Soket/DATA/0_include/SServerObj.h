#pragma once
#include "SvrStd.h"
class SServerObj
{
public:
	CRITICAL_SECTION	m_cs; // �Ӱ� ����,
public:
	SServerObj(void);
	virtual ~SServerObj(void);
};

