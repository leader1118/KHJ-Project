#pragma once
#include "sWindow.h"
#include "sTimer.h"
#include "sInput.h"
#include "sDxState.h"
#include "sWrite.h"
#include "xSkyBox.h"
#include "xModelView.h"

using namespace DX;

class sCore : public sWindow
{
public:
	xSkyBox     m_SkyBox;
	sTimer		m_Timer;
	sWrite		m_Font;
	xCamera     m_DefaultCamera;
	xModelView  m_ModelCamera;
	xCamera*	m_pMainCamera;
	xDirLineShape   m_dirAxis;
public:
	virtual bool	GamePreInit();
	bool	GameInit();
	bool	GameRun();
	bool	GameRelease();
	bool	GameFrame();
	bool	GameRender();
	bool	GamePreRender();
	bool	GamePostRender();

	void    DeleteDeviceResources();
	HRESULT CreateDeviceResources(UINT width, UINT height);
	virtual void    DeleteResources() {};
	virtual HRESULT CreateResources(UINT width, UINT height) { return S_OK; }
public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	PreRender() { return true; }
	virtual bool	PostRender() { return true; }
	virtual bool	Release() { return true; }
	LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	void    SwapDefaultView();
	void    SwapModelView();
public:
	sCore();
	virtual ~sCore();
};