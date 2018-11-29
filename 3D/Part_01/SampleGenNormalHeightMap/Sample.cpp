#include "xCore.h"
#include "xMap.h"
class Sample : public xCore
{
	xMap   m_map;
	xLineShape		m_ObjLine;
public:
	bool Init()
	{
		m_pMainCamera->SetViewMatrix(
			D3DXVECTOR3(0.0f, 300.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_ObjLine.Create(m_pd3dDevice,
			L"../../Include/data/shader/shape.hlsl",
			L"../../Include/data/eye.bmp");

		xMapDesc desc = { 5, 5, 1.0f, 1.0f,
				L"../../Include/data/map/Tile40.jpg", 
				L"../../Include/data/shader/map.hlsl",
				};
		m_map.Init();
		m_map.CreateHeightMap(m_pd3dDevice,
			m_pContext, 
			L"../../Include/data/map/heightMap513.bmp");
		desc.iNumRows = m_map.m_iNumRows;
		desc.iNumCols = m_map.m_iNumCols;
		desc.fScaleHeight = 1.0f;
		if (m_map.Load(m_pd3dDevice,desc)==false)
		{
			return false;
		}
	}
	bool Render()
	{
		m_map.SetMatrix(NULL, &m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		m_map.Render(m_pContext);


		for (int iVertex = 0; iVertex < m_map.m_VertexList.size(); iVertex+=10000)
		{
			D3DXVECTOR3 vNormal = m_map.m_VertexList[iVertex].n;
			m_ObjLine.SetMatrix(NULL,&m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
			m_ObjLine.Draw(m_pContext, 
				m_map.m_VertexList[iVertex].p, 
				m_map.m_VertexList[iVertex].p+vNormal*10.0f);
		}
		return true;
	}
	bool Release()
	{
		return m_map.Release();
	}
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("Sample", 800, 600)
