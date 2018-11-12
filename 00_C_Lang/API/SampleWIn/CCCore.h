#pragma once
#include "CCWindow.h"
#include "CCTimer.h"
#include "CCInput.h"
class CCCore : public CCWindow
{
public:
	CCTimer		m_Timer;
	CCInput		m_Input;
	HDC			m_hScreenDC; //전면 버퍼
	HBITMAP		m_hOldBitmap; //후면 버퍼의 이미지

	HDC			m_hOffScreenDC; // 후면 버퍼
	HBITMAP		m_hOffScreenBitmap;// 후면버퍼의 이미지
public:
	bool		GameRun();
	bool		GameInit();
	bool		GameFrame();
	bool		GameRender();
	bool		GameRelease();
	void		MsgEvent(MSG msg);

	bool		DrawDebug();
	bool		PreRender();
	bool		PostRender();
public:
	////////가상 함수들////////
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }
public:
	CCCore();
	virtual ~CCCore();
};

