#pragma once
#include "Sstd.h"
#include "xShape.h"
struct xPlane
{
	float a, b, c, d;
	void   CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
	{
		D3DXVECTOR3 vEdge0 = v1 - v0;
		D3DXVECTOR3 vEdge1 = v2 - v0;
		D3DXVECTOR3 vNormal;
		D3DXVec3Cross(&vNormal, &vEdge0, &vEdge1);
		D3DXVec3Normalize(&vNormal, &vNormal);
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		d = -(v0.x*a + v0.y*b + v0.z*c);
	}
	void   CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 vNormal)
	{
		D3DXVec3Normalize(&vNormal, &vNormal);
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		d = -(v0.x*a + v0.y*b + v0.z*c);
	}
	xPlane() { a = b = c = d = 0.0f; }
};
class xFrustum
{
private:
	D3DXMATRIX m_mWorld;
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
public:
	xPlane			m_Plane[6];
	D3DXVECTOR3		m_vFrustum[8];
public:
	void   SetMatrix(	D3DXMATRIX* pWorld,
						D3DXMATRIX* pView, 
						D3DXMATRIX* pProj);
	bool    CreateFrustum();
	bool	ClassifyPoint(D3DXVECTOR3 v0);
	bool	ClassifySphere(D3DXVECTOR3 v, float fRadius);
public:
	xFrustum();
	virtual ~xFrustum();
};

