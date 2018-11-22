#pragma once
#include "xCamera.h"
class SArcBall
{
public:
	bool				m_bDrag;

	D3DXVECTOR3			m_vDownPT;
	D3DXVECTOR3			m_vCurrentPT;

	D3DXQUATERNION		m_qNow;
	D3DXQUATERNION		m_qDown;

public:
	D3DXMATRIX GetRotationMatrix();
	D3DXVECTOR3	ScreenToVector(float fX,float fY);
	D3DXQUATERNION QuatFromBallPoints(D3DXVECTOR3 m_vDownPt, D3DXVECTOR3 m_vCurrentPt);
	void OnBegin(int x, int y);
	void OnMove(int x, int y);
	void OnEnd();
public:
	SArcBall();
	virtual ~SArcBall();
};

