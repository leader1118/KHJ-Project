#pragma once
#include "sWindow.h"


class sCore : public sWindow
{
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

