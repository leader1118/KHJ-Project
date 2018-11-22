#include "xFrustum.h"
// ���ð� ���ݴ� �������� ������
void	 xFrustum::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_mWorld = *pWorld;
	}
	if (pView != NULL)
	{
		m_mView = *pView;
	}
	if (pProj != NULL)
	{
		m_mProj = *pProj;
	}
}

bool	xFrustum::CreateFrustum()
{
	D3DXMATRIX	matInvViewProj;// =m_mView*m_mProj;
	D3DXMatrixMultiply(&matInvViewProj, &m_mView, &m_mProj);

	D3DXMatrixInverse(&matInvViewProj, NULL, &matInvViewProj);

	// ��
	// 5	6
	// 4	7
	// ��
	// 1	2
	// 0	3
	m_vFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vFrustum[1] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vFrustum[2] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vFrustum[3] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	m_vFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vFrustum[5] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vFrustum[6] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vFrustum[7] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	for (int iVertex = 0; iVertex < 8; iVertex++)
	{
		D3DXVec3TransformCoord(&m_vFrustum[iVertex], &m_vFrustum[iVertex], &matInvViewProj);
	}
	// ��
	// 5	6
	// 4	7
	// ��
	// 1	2
	// 0	3
	m_Plane[0].CreatePlane(m_vFrustum[0], m_vFrustum[1], m_vFrustum[2]); // -z ��
	m_Plane[1].CreatePlane(m_vFrustum[6], m_vFrustum[5], m_vFrustum[4]); // +z ��
	
	m_Plane[2].CreatePlane(m_vFrustum[2], m_vFrustum[6], m_vFrustum[7]); // +x ��
	m_Plane[3].CreatePlane(m_vFrustum[5], m_vFrustum[1], m_vFrustum[0]); // -x ��
	
	m_Plane[4].CreatePlane(m_vFrustum[1], m_vFrustum[5], m_vFrustum[6]); // -z ��
	m_Plane[5].CreatePlane(m_vFrustum[0], m_vFrustum[3], m_vFrustum[7]); // +z ��
	return true;
}
bool xFrustum::ClassifyPoint(D3DXVECTOR3 v0) // ������ �׽�Ʈ
{
	for (int iplane = 0; iplane < 6; iplane++)
	{
		float fDistance = m_Plane[iplane].a*
			v0.x+
			m_Plane[iplane].b*
			v0.y+
			m_Plane[iplane].c*
			v0.z+
			m_Plane[iplane].d;

		if (fDistance > 0.0f)
		{
			return false;
		}
	}
	return true;
}
bool xFrustum::ClassifySphere(D3DXVECTOR3 v0,float fRadius) // ������ �׽�Ʈ //
{
	for (int iplane = 0; iplane < 6; iplane++)
	{
		float fDistance = m_Plane[iplane].a*
			v0.x +
			m_Plane[iplane].b*
			v0.y +
			m_Plane[iplane].c*
			v0.z +
			m_Plane[iplane].d;

		/*if (fDistance > 0.0f)
		{	
			if (fDistance > fRadius)
			{
				return false;
			}
		}*/
		if (fDistance > fRadius)
		{
			return false;
		}
	}
	return true;
}
xFrustum::xFrustum()
{
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mProj);
}


xFrustum::~xFrustum()
{
}
