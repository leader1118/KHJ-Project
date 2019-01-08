#include "SActor.h"

D3DXVECTOR3 SActor::Gen(float x, float y)
{
	D3DXVECTOR3 vRet;

	vRet.x = x / 800;
	vRet.y = y / 600;
	vRet.x = vRet.x*2.0f - 1.0f;
	vRet.y = (vRet.y * 2 - 1.0f)*-1.0f;
	return vRet;
}

void SActor::GenCenter()
{
	m_vCenter.x = 0.0f;
	m_vCenter.y = 0.0f;
	for (int iV = 0; iV < 6; iV++)
	{
		D3DXVECTOR3 vertex = m_VertexList[iV].p;
		m_vCenter.x += vertex.x;
		m_vCenter.y += vertex.y;
	}
	m_vCenter.x /= 6.0f;
	m_vCenter.y /= 6.0f;
}

bool SActor::Setdata(UINT left, UINT top, UINT width, UINT height)
{
	m_rtInit.left = left;
	m_rtInit.right = width;
	m_rtInit.top = top;
	m_rtInit.bottom = height;
	SetVertexData();
	return true;
}

void SActor::SetVertexData()
{
	D3DXVECTOR3 pos = Gen(m_rtInit.left, m_rtInit.top);
	m_VertexList[0].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_VertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	
	pos = Gen(m_rtInit.left + m_rtInit.right, m_rtInit.top);
	m_VertexList[1].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_VertexList[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_VertexList[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	pos = Gen(m_rtInit.left, m_rtInit.top + m_rtInit.bottom);
	m_VertexList[2].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_VertexList[2].t = D3DXVECTOR2(0.0f, 1.0f);
	m_VertexList[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[3] = m_VertexList[2];
	m_VertexList[4] = m_VertexList[1];
	
	pos = Gen(m_rtInit.left + m_rtInit.right, m_rtInit.top + m_rtInit.bottom);
	m_VertexList[5].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_VertexList[5].t = D3DXVECTOR2(1.0f, 1.0f);
	m_VertexList[5].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	GenCenter();
}

bool SActor ::Frame(float fGameTimer,float fFps)
{
	return true;
}

bool SActor::PreRender(ID3D11DeviceContext* pContext, UINT iVertexSize)
{
	m_dxObj.PreRender(pContext, iVertexSize);
	return true;
}
bool SActor::Render(ID3D11DeviceContext* pContext, UINT iVertexSize, UINT iCount)
{
	m_dxObj.Render(pContext, iVertexSize, iCount);
	return true;
}
bool SActor::PostRender(ID3D11DeviceContext* pContext, UINT iVertexSize, UINT iCount)
{
	m_dxObj.PostRender(pContext, iVertexSize, iCount);
	return true;
}
bool SActor::Init()
{
	return true;
}
bool SActor::Release()
{
	m_dxObj.Release();
	return true;
}


SActor::SActor()
{
}


SActor::~SActor()
{
}
