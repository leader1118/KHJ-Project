#include "TCore.h"

HDC g_hOffScreenDC = NULL;

bool	TCore::GameInit() 
{	
	m_Timer.Init();
	I_Input.Init();

	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	g_hOffScreenDC = m_hOffScreenDC;

	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC, m_rtClient.right,
		m_rtClient.bottom);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	COLORREF bkColor = RGB(255, 0, 0);
	m_hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, m_hbrBack);

	
	Init();
	return true;
}
bool	TCore::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();	
	Frame();
	return true;
}
bool	TCore::GamePreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0,
		m_rtClient.right,
		m_rtClient.bottom,
		PATCOPY);
	return true;
}
bool	TCore::GamePostRender()
{
	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right,
		m_rtClient.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}
bool	TCore::GameRender()
{
	GamePreRender();
	{
		Render();
		m_Timer.Render();
		I_Input.Render();
	}
	GamePostRender();
	return true;
}
bool	TCore::GameRun() 
{
	GameFrame();	
	GameRender();
	return true;
}
bool	TCore::GameRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();

	DeleteObject(m_hbrBack);
	DeleteObject(m_hOffScreenBitmap);
	ReleaseDC(m_hWnd, m_hScreenDC);
	ReleaseDC(m_hWnd, m_hOffScreenDC);
	return true;
}
TCore::TCore()
{
}


TCore::~TCore()
{
}
