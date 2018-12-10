#include "xCore.h"
LRESULT	xCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return m_ModelCamera.MsgProc(hWnd, msg, wParam, lParam);
}
void xCore::DeleteDeviceResources() 
{
	if (m_pDSV)m_pDSV->Release();
	m_Font.DiscardDeviceResources();
	DeleteResources();
}
HRESULT xCore::CreateDeviceResources(UINT width, UINT height) 
{
	IDXGISurface* pBackBuffer=nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		(void**)&pBackBuffer);
	HRESULT hr = m_Font.CreateDeviceResources(pBackBuffer);
	pBackBuffer->Release();

	CreateDSV();
	m_pMainCamera->UpdateProjMatrix(width, height);

	CreateResources(width, height);
	return hr;
}
bool	xCore::GamePreInit()
{
	return false;
}
bool	xCore::GameInit()
{	
	GamePreInit();
	
	xDevice::Init();
	m_Timer.Init();
	m_Font.Init();
	I_Input.Init();

	IDXGISurface* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),(void**)&pBackBuffer);
	m_Font.Set(m_hWnd,m_sd.BufferDesc.Width,m_sd.BufferDesc.Height, pBackBuffer);
	pBackBuffer->Release();

	xDxState::SetState(m_pd3dDevice);

	m_DefaultCamera.SetViewMatrix();
	m_DefaultCamera.SetProjMatrix(D3DX_PI * 0.25f,(float)m_rtClient.right/ (float)m_rtClient.bottom );
	
	m_ModelCamera.SetViewMatrix();
	m_ModelCamera.SetProjMatrix(D3DX_PI * 0.25f, (float)m_rtClient.right / (float)m_rtClient.bottom);

	m_pMainCamera = &m_DefaultCamera;

	m_SkyBox.Create(m_pd3dDevice,
		L"../../data/shader/sky.hlsl",
		L"../../data/grassenvmap1024.dds");

	m_dirAxis.Create(m_pd3dDevice,L"../../data/shader/shape.hlsl",L"../../data/eye.bmp");

	Init();
	return true;
}
void    xCore::SwapModelView()
{
	m_pMainCamera = &m_ModelCamera;
}
void    xCore::SwapDefaultView()
{
	m_pMainCamera = &m_DefaultCamera;
}
bool	xCore::GameFrame()
{	
	m_Timer.Frame();
	I_Input.Frame();
	
	D3DXVECTOR4   vYawPitchRoll(0,0,0,0);
	// camera control
	if (g_Input.bButton1)
	{
		vYawPitchRoll.y = 0.1f * D3DXToRadian(I_Input.m_MouseState.lX);
		vYawPitchRoll.x = 0.1f * D3DXToRadian(I_Input.m_MouseState.lY);
	}
	float fValue = I_Input.m_MouseState.lZ;
	vYawPitchRoll.w = fValue *g_fSecPerFrame;
	if (g_Input.bJump)
	{
		m_pMainCamera->SetSpeed(g_fSecPerFrame*3.0f);
	}
	if (g_Input.bFront)
	{
		m_pMainCamera->MoveLook(g_fSecPerFrame*5.0f);
	}
	if (g_Input.bBack)
	{
		m_pMainCamera->MoveLook(-g_fSecPerFrame*5.0f);
	}
	if (g_Input.bLeft)
	{
		m_pMainCamera->MoveSide(-g_fSecPerFrame * 5.0f);
	}
	if (g_Input.bRight)
	{
		m_pMainCamera->MoveSide(g_fSecPerFrame*5.0f);
	}
	m_pMainCamera->Update(vYawPitchRoll);
	m_pMainCamera->Frame();

	m_SkyBox.Frame();

	Frame();

	m_dirAxis.Frame();
	return true;
}
bool	xCore::GamePreRender()
{
	float color[4] = { 0.44f,0.61f,0.83f,1 };
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);
	m_pContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pContext->OMSetRenderTargets(1,&m_pRenderTargetView, m_pDSV);

	ApplyDSS(m_pContext, xDxState::g_pDSVStateEnableLessEqual);
	ApplyBS(m_pContext, xDxState::g_pBSAlphaBlend);
	//ApplyRS(m_pContext, xDxState::g_pRSBackCullSolid);
	ApplySS(m_pContext, xDxState::g_pSSWrapLinear);

	if (I_Input.m_KeyState[DIK_P])
		ApplyRS(m_pContext, xDxState::g_pRSWireFrame);
	else
		ApplyRS(m_pContext, xDxState::g_pRSNoneCullSolid);

	m_pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_SkyBox.SetMatrix(NULL,
		&m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);
	m_SkyBox.Render(m_pContext);

	return true;
}
bool	xCore::GamePostRender()
{
	m_Timer.Render();
	RECT rt = g_rtClient;
	m_Font.Render();
	m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	m_Font.DrawText(rt, m_Timer.m_csBuffer, D2D1::ColorF(0, 0, 0, cosf(m_Timer.m_fGameTimer)*0.5f + 0.5f));

	m_dirAxis.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_dirAxis.Render(m_pContext);

	m_pSwapChain->Present(0, 0);
	return true;
}
bool	xCore::GameRender()
{
	GamePreRender();
	{
		PreRender();	
		Render();
		PostRender();
	}
	GamePostRender();
	return true;
}
bool	xCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool	xCore::GameRelease()
{
	Release();	

	m_ModelCamera.Release();
	m_DefaultCamera.Release();

	m_SkyBox.Release();
	m_Timer.Release();
	m_Font.Release();
	I_Input.Release();
	m_dirAxis.Release();
	xDxState::Release();
	xDevice::Release();
	return true;
}
xCore::xCore()
{
	m_pMainCamera = NULL;
}


xCore::~xCore()
{
}
