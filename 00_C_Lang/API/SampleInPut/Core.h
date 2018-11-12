#pragma once
#include "Window.h"
#include "Timer.h"

class Core : public Window
{
public:
	Timer  m_Timer;
public:
	bool	GameInit();
	bool	GameRun();
	bool	GameRelease();
	bool	GameFrame();
	bool	GameRender();
public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }
public:
	Core();
	virtual ~Core();
};

