#pragma once
#include "S_Window.h"
#include "S_Input.h"
#include "S_Time.h"
class S_Core : public S_Window
{
public:
	S_Time		m_Timer;
	HDC			m_hScreenDC;  
	HBITMAP		m_hOldBitmap; 

	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap; 	

	HBRUSH		m_hbrBack;
	HBRUSH		m_hbrOld;

	HANDLE		m_hPen;
	HANDLE		m_hOldPen;

	HFONT		m_fontDefault;
	HFONT		m_fontDefaultOld;
public:
	bool	GameRun();
	bool	GameInit();
	bool	GameFrame();
	virtual bool	GameRender();
	bool    GameRelease();
	bool	ResizeClient(UINT iWidth, UINT iHeight);
	virtual bool	DrawDebug();
	virtual bool    DrawDebug(TCHAR* pString, int iX, int iY);
	virtual bool	PreRender();
	virtual bool	PostRender();
public:
	virtual bool		Init() { return true; }
	virtual bool		PreFrame() { return true; }
	virtual bool		PostFrame() { return true; }
	virtual bool		Frame() { return true; }
	virtual bool		Render() { return true; }
	virtual bool		Release() { return true; };

public:
	S_Core();
	virtual ~S_Core();
};

