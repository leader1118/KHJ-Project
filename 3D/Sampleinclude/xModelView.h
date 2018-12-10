#pragma once
#include "xArcBall.h"
class xModelView : public xCamera
{
	xArcBall   m_WorldArcBall;
public:
	LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Update(D3DXVECTOR4 vValue);
public:
	xModelView();
	virtual ~xModelView();
};

