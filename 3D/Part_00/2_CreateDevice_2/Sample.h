#pragma once
#include "DXWindow.h"
#include "DXDevice.h"

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