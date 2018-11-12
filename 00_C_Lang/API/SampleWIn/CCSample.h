#pragma once
#include "CCCore.h"

class CCSample : public CCCore
{
public:
	bool		Init();
	bool		Frame();
	bool		Render();
public:
	CCSample();
	virtual ~CCSample();
};

