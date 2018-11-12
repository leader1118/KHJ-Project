#pragma once
#include "CCWindow.h"
#include "CCTimer.h"
#include "CCInput.h"
class CCCore : public CCWindow
{
public:
	CCTimer		m_Timer;
	CCInput		m_Input;
	HDC			m_hScreenDC; //���� ����
	HBITMAP		m_hOldBitmap; //�ĸ� ������ �̹���

	HDC			m_hOffScreenDC; // �ĸ� ����
	HBITMAP		m_hOffScreenBitmap;// �ĸ������ �̹���
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
	////////���� �Լ���////////
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }
public:
	CCCore();
	virtual ~CCCore();
};

