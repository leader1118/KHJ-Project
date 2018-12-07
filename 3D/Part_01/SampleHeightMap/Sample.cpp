#include "xCore.h"
#include "xMap.h"
class Sample : public xCore
{
	xMap   m_map;
public:
	bool Init()
	{
		m_pMainCamera->SetViewMatrix(
			D3DXVECTOR3(0.0f, 300.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
		desc.fScaleHeight = 0.5f;
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