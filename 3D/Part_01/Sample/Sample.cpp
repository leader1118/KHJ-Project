#include "xCore.h"
class Sample : public xCore
{
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("Sample", 800, 600)





//#include "xCore.h"
//#include "xShape.h"
//
//class Sample : public xCore
//{
//	xBoxShape m_ObjBox;
//	xPlaneShape m_ObjPlane;
//	xLineShape m_ObjLine;
//	xSphereShape m_ObjSphere;
//public:
//	void    DeleteResources()
//	{
//	}
//	HRESULT CreateResources(UINT width, UINT height)
//	{
//		return S_OK;
//	}
//	bool Init()
//	{
//		m_pMainCamera->SetViewMatrix(
//			D3DXVECTOR3(0.0f, 0.0f, -5.0f),
//			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//		m_ObjLine.Create(m_pd3dDevice,
//			L"../../Include/data/shader/shape.hlsl",
//			L"../../Include/data/eye.bmp");		
//
//		m_ObjBox.Create(m_pd3dDevice, 
//			L"../../Include/data/shader/shape.hlsl",
//			L"../../Include/data/eye.bmp");	
//
//		m_ObjPlane.Create(m_pd3dDevice,
//			L"../../Include/data/shader/shape.hlsl",
//			L"../../Include/data/eye.bmp");
//
//
//		m_ObjSphere.Create(m_pd3dDevice,
//			L"../../Include/data/shader/shape.hlsl",
//			L"../../Include/data/eye.bmp");
//		return true;
//	}
//	bool Frame()
//	{
//		m_ObjLine.Frame();
//		m_ObjPlane.Frame();
//		m_ObjSphere.Frame();
//		return m_ObjBox.Frame();
//	}
//	bool Render()	
//	{
//		D3DXMATRIX matWorld, matRot;
//		D3DXMatrixTranslation(&matWorld,3.0f, 0, 0);
//		D3DXMatrixRotationY(&matRot,m_Timer.m_fGameTimer);
//		matWorld = matWorld * matRot;
//		//ApplyRS(m_pContext, xDxState::g_pRSNoneCullSolid);
//		// �� ���
//		m_ObjPlane.SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
//		m_ObjPlane.Render(m_pContext);
//		//ApplyRS(m_pContext, xDxState::g_pRSBackCullSolid);
//
//		// �� ���
//		//ApplyRS(m_pContext, xDxState::g_pRSWireFrame);
//		D3DXMatrixTranslation(&matWorld,	-3.0f, 0, 0);
//		m_ObjSphere.SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
//		m_ObjSphere.Render(m_pContext);
//
//		// �ڽ� ���
//		m_ObjBox.SetMatrix(NULL,&m_pMainCamera->m_matView,&m_pMainCamera->m_matProj);
//		m_ObjBox.Render(m_pContext);
//
//		// �ڽ��� ���� ���ἱ ���
//		m_ObjLine.Draw(m_pContext,m_ObjBox.m_vPosition,m_ObjPlane.m_vPosition,D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f));
//		
//		// �� ���⺤�� ���
//		m_ObjLine.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);		
//		D3DXVECTOR3 vDir = m_ObjPlane.m_vLook * 10.0f;		
//		m_ObjLine.Draw(m_pContext, m_ObjPlane.m_vPosition,m_ObjPlane.m_vPosition+ vDir,	D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) );
//		vDir = m_ObjPlane.m_vUp * 10.0f;
//		m_ObjLine.Draw(m_pContext,m_ObjPlane.m_vPosition,m_ObjPlane.m_vPosition + vDir,	D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
//		vDir = m_ObjPlane.m_vSide * 10.0f;
//		m_ObjLine.Draw(m_pContext,m_ObjPlane.m_vPosition,m_ObjPlane.m_vPosition + vDir,	D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
//		return true;
//	}
//	bool Release()
//	{
//		m_ObjLine.Release();
//		m_ObjSphere.Release();
//		m_ObjPlane.Release();
//		return m_ObjBox.Release();
//	}
//public:
//	Sample() {
//	}
//	~Sample() {}
//};
//GAME_RUN("Sample", 800, 600)