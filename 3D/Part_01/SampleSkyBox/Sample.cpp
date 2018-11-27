#include "xCore.h"

class Sample : public xCore
{
	xBoxShape			m_ObjBox;
	xPlaneShape			m_ObjPlane;
	xLineShape			m_ObjLine;
	xSphereShape		m_ObjSphere;
	D3DXMATRIX			m_World[100];
public:
	void DeleteResources()
	{

	}
	HRESULT CreateResources(UINT width, UINT height)
	{
		return S_OK;
	}
	bool Init()
	{
		D3DXMatrixIdentity(&m_World[0]);
		for (int iObj = 1; iObj < 100; iObj++)
		{
			m_World[iObj] = m_World[0];
			m_World[iObj]._43 = iObj * 10;
		}
		// 모델뷰 카메라 전환
		SwapModelView();

		m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_ObjLine.Create(m_pd3dDevice,
			L"../../Include/data/shader/shape.hlsl",
			L"../../Include/data/eye.bmp");

		m_ObjBox.Create(m_pd3dDevice,
			L"../../Include/data/shader/shape.hlsl",
			L"../../Include/data/eye.bmp");

		m_ObjPlane.Create(m_pd3dDevice,
			L"../../Include/data/shader/shape.hlsl",
			L"../../Include/data/eye.bmp");


		m_ObjSphere.Create(m_pd3dDevice,
			L"../../Include/data/shader/shape.hlsl",
			L"../../Include/data/eye.bmp");
		return true;
	}
	bool Frame()
	{
		m_ObjLine.Frame();
		m_ObjPlane.Frame();
		m_ObjSphere.Frame();
		return m_ObjBox.Frame();
	}

	bool Render()
	{
		// 박스 출력
		int iRenderCnt = 0;
		for (int iObj = 0; iObj < 100; iObj++)
		{
			D3DXVECTOR3 vPos;
			vPos.x = m_World[iObj]._41;
			vPos.y = m_World[iObj]._42;
			vPos.z = m_World[iObj]._43;
			m_World[iObj] = m_pMainCamera->m_matWorld;
			m_World[iObj]._41 = vPos.x;
			m_World[iObj]._42 = vPos.y;
			m_World[iObj]._43 = vPos.z;

			if (m_pMainCamera->ClassifySphere(vPos, 1.44f))
			{
				m_ObjBox.SetMatrix(&m_World[iObj],
					&m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
				m_ObjBox.Render(m_pContext);
				iRenderCnt++;
			}
		}
		return true;
	}
	bool Release()
	{
		m_ObjLine.Release();
		m_ObjSphere.Release();
		m_ObjPlane.Release();
		return m_ObjBox.Release();
	}
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SampleSkyBox", 800, 600);