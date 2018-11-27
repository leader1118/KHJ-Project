#include "xCore.h"
#include "xMap.h"

class Sample : public xCore
{
public :
	xMap m_Map;
public:
	bool Init()
	{
		m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 50.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		xMapDesc desc = { 257,257,1.0f,1.0f,L"../../Include/data/Eye.bmp",
										L"../../Include/data/shader/shape.hlsl" };
		m_Map.Init();
		if (m_Map.Load(m_pd3dDevice,desc) == false)
		{
			return false;
		}
	}
	bool Render()
	{
		m_Map.SetMatrix(NULL,&m_pMainCamera->m_matView,&m_pMainCamera->m_matProj);
		m_Map.Render(m_pContext);
		return true;
	}
	bool Release()
	{
		return m_Map.Release();
	}
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SampleMap", 800, 600);