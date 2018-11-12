#include "Core.h"


bool	Core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();

	Init();
	return true;
}
bool	Core::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	Frame();
	return true;
}
bool	Core::GameRender()
{
	Render();

	m_Timer.Render();
	I_Input.Render();
	return true;
}
bool	Core::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool	Core::GameRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();
	return true;
}
Core::Core()
{
}


Core::~Core()
{
}
