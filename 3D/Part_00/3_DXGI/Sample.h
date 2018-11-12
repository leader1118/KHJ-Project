#pragma once
#include "DXWindow.h"
#include "DXEnumeration.h"

class Sample : public DXWindow
{
public:
	bool	Init();
	bool	Render();
	bool	Release();
public:
	Sample(void);
	~Sample(void);
};