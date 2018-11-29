#include "xCore.h"
#include "xMap.h"
class Sample : public xCore
{
	xMap   m_map;
public:
	bool Init()
	{
		m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 50.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		xMapDesc desc = { 257, 257, 1.0f, 1.0f,
			L"../../Include/data/Eye.bmp",
			L"../../Include/data/shader/shape.hlsl" };
		m_map.Init();
		if (m_map.Load(m_pd3dDevice, desc) == false)
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
