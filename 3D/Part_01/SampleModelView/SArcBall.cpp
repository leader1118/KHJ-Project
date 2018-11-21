#include "SArcBall.h"

void SArcBall::OnBegin(int x, int y)
{
	m_bDrag = true;
	m_qDown = m_qNow;
	m_vDownPT = ScreenToVector(x, y);
}
// 2D->3D·Î º¯È¯ 
D3DXVECTOR3	SArcBall::ScreenToVector(float fX, float fY)
{
	// fx*fx + fy*fy + fz*fz = r*r;
	float fHalfX = -(g_rtClient.right / 2.0f);;
	float fHalfY = (g_rtClient.bottom / 2.0f);
		float x = (fX - fHalfX) / fHalfX;
	float y = (fY - fHalfY) / fHalfY;
	float z = 0.0f;
	float fFlag = (x*x + y * y);
	if (fFlag > 1.0f)
	{
		x *= (1.0f/sqrtf(fFlag));
		y *= (1.0f / sqrtf(fFlag));
	}
	else
	{
		z = sqrtf(1.0f - fFlag);
	}
	return D3DXVECTOR3(x, y, z);
}

D3DXQUATERNION SArcBall::QuatFromBallPoints(D3DXVECTOR3 m_vDownPT, D3DXVECTOR3 m_vCurrentPT)
{
	float fDot = D3DXVec3Dot(&m_vDownPT, &m_vCurrentPT);
	D3DXVECTOR3 vPart;
	D3DXVec3Cross(&vPart, &m_vDownPT, &m_vCurrentPT);
	D3DXQUATERNION qRet(vPart.x,vPart.y,vPart.z,fDot);
	return qRet;
}
void SArcBall::OnMove(int x, int y)
{
	if (m_bDrag)
	{
		m_vCurrentPT = ScreenToVector(x, y);
		m_qNow = m_qDown * QuatFromBallPoints(m_vDownPT, m_vCurrentPT);
	}
}
void SArcBall::OnEnd()
{
	m_bDrag = false;
}

SArcBall::SArcBall()
{
	m_bDrag = false;
	m_vDownPT = D3DXVECTOR3(0, 0, 0);
	m_vCurrentPT = D3DXVECTOR3(0, 0, 0);
	D3DXQuaternionIdentity(&m_qNow);
	D3DXQuaternionIdentity(&m_qDown);
}


SArcBall::~SArcBall()
{
}
