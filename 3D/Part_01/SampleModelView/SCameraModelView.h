#pragma once
#include "SArcBall.h"
class SCameraModelView : public xCamera
{
public:
	
	SArcBall m_WorldArcBall;
public: 
	virtual bool Update(D3DXVECTOR4 vValue);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	D3DXQUATERNION QuatFromBallpoints();
public:
	SCameraModelView();
	virtual ~SCameraModelView();
};

