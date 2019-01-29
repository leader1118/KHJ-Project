#include "S_Viewer.h"
#include "TObjMgr.h"

bool S_Viewer::Init()
{
	I_CharMgr.Init();

	if(!I_CharMgr.Load(g_pd3dDevice, m_pContext,_T("CharacterTable.cit")))
	{
		return false;
	}

	shared_ptr<S_HeroObj> pObjA = make_shared<S_HeroObj>();
	pObjA->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR0");
	pObjA->m_pBoneObject = pObjA->m_pChar->m_pBoneObject;
	pObjA->SetActionFrame(pObjA->m_pBoneObject->m_Scene.iFirstFrame, pObjA->m_pBoneObject->m_Scene.iLastFrame);
	m_HeroObj.push_back(pObjA);

	shared_ptr<S_HeroObj> pObjB = make_shared<S_HeroObj>();
	pObjB->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR1");
	if (pObjB->m_pChar)
	{
		pObjB->m_pBoneObject = pObjB->m_pChar->m_pBoneObject;
		pObjB->SetActionFrame(pObjB->m_pBoneObject->m_Scene.iFirstFrame, 60);
		m_HeroObj.push_back(pObjB);
	}

	shared_ptr<S_HeroObj> pObjC = make_shared<S_HeroObj>();
	pObjC->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR1");
	if (pObjC->m_pChar)
	{
		pObjC->m_pBoneObject = m_HeroObj[1]->m_pChar->m_pBoneObject;
		pObjC->SetActionFrame(61, 91);
		m_HeroObj.push_back(pObjC);
	}

	shared_ptr<S_HeroObj> pObjD = make_shared<S_HeroObj>();
	pObjD->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR1");
	if (pObjD->m_pChar)
	{
		pObjD->m_pBoneObject = m_HeroObj[1]->m_pChar->m_pBoneObject;
		pObjD->SetActionFrame(92, 116);
		m_HeroObj.push_back(pObjD);
	}

	shared_ptr<S_HeroObj> pObjE = make_shared<S_HeroObj>();
	pObjE->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR2");
	if (pObjE->m_pChar)
	{
		pObjE->m_pBoneObject = pObjE->m_pChar->m_pBoneObject;
		pObjE->SetActionFrame(pObjE->m_pBoneObject->m_Scene.iFirstFrame, pObjE->m_pBoneObject->m_Scene.iLastFrame);
		m_HeroObj.push_back(pObjE);
	}

	shared_ptr<S_HeroObj> pObjF = make_shared<S_HeroObj>();
	pObjF->m_pChar = I_CharMgr.GetPtr(L"TEST_CHAR3");
	if (pObjF->m_pChar)
	{
		pObjF->m_pBoneObject = pObjF->m_pChar->m_pBoneObject;
		pObjF->SetActionFrame(pObjF->m_pBoneObject->m_Scene.iFirstFrame, pObjF->m_pBoneObject->m_Scene.iLastFrame);
		m_HeroObj.push_back(pObjF);
	}
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<xCamera>();
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(-100.0f, 30.0f, -100.0f), D3DXVECTOR3(100.0f, 30.0f, 100.0f));


	float fAspectRatio = 800 / (FLOAT)600;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f);
	//m_pMainCamera->SetWindow(800, 600);
	return true;
}
bool S_Viewer::Render()
{
	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		m_matWorld._41 = -50.0f + iChar * 25.0f;
		m_HeroObj[iChar]->SetMatrix(&m_matWorld,&m_pMainCamera->m_matView,&m_pMainCamera->m_matProj);
		m_HeroObj[iChar]->Render(m_pContext);
	}
	return true;
}

bool S_Viewer()
{
	I_CharMgr.Release();
	return true;
}
bool S_Viewer::Frame()
{
	float t = m_Timer.GetElapsedTime() * D3DX_PI;
	//m_pMainCamera->Update(g_fSecPerFrame);
	m_pMainCamera->Frame();
	m_matWorld = m_pMainCamera->m_matWorld;
	m_matWorld._41 = 0.0f;
	m_matWorld._42 = 0.0f;
	m_matWorld._43 = 0.0f;

	for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
	{
		if (I_Input.m_KeyState[DIK_ADD])
		{
			m_HeroObj[iChar]->m_fSpeed += g_fSecPerFrame;
		}
		if (I_Input.m_KeyState[DIK_SUBTRACT])
		{
			m_HeroObj[iChar]->m_fSpeed -= g_fSecPerFrame;
			if (m_HeroObj[iChar]->m_fSpeed < 0.0f) m_HeroObj[iChar]->m_fSpeed = 0.01f;
		}
		m_HeroObj[iChar]->Frame();
	}
	if (I_Input.m_KeyState[DIK_F3] == KEY_UP && m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame(120, 205);//jump		
	}
	if (I_Input.m_KeyState[DIK_F4] == KEY_UP && m_HeroObj.size() > 1)
	{
		m_HeroObj[1]->SetActionFrame(205, 289);//attack		
	}

	if (I_Input.m_KeyState[DIK_F5] == KEY_UP)
	{
		for (int iChar = 0; iChar < m_HeroObj.size(); iChar++)
		{
			m_HeroObj[iChar]->m_bBoneRender = !m_HeroObj[iChar]->m_bBoneRender;
		}
	}
	return true;
}

HRESULT S_Viewer::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera)
	{
		float fAspectRatio = m_sd.BufferDesc.Width / (float)m_sd.BufferDesc.Height;
		m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return S_OK;
}

HRESULT S_Viewer::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pContext)m_pContext->ClearState();
	return S_OK;
}

S_Viewer::S_Viewer(void)
{
}


S_Viewer::~S_Viewer(void)
{
}

int S_Viewer::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}
GAME_RUN(L"Bindpose Viewer",800,600);