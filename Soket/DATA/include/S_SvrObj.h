#pragma once

#include "S_Std.h"

class S_SvrObj
{
public:
	CRITICAL_SECTION m_Ct;
public:
	S_SvrObj();
	virtual ~S_SvrObj();
};

