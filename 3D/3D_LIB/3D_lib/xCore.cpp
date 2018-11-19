#include "xCore.h"
void xCore::DeleteDeviceResources() 
{
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
	if (FAILED(CreateDevice()))
	{
		return false;
	}
	if (FAILED(CreateGIFactory()))
	{
		return false;
	}
	if (FAILED(CreateSwapChain()))
	{
		return false;
	}
	if (FAILED(SetRenderTargetView()))
	{
		return false;
	}
	SetViewPort();
	CreateDSV();

	xDxState::SetState(m_pd3dDevice);

	m_pDXGIFactory->MakeWindowAssociation(m_hWnd,
		DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);


	m_Timer.Init();
	m_Font.Init();
	m_Input.Init();
	IDXGISurface* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		(void**)&pBackBuffer);
	m_Font.Set(m_hWnd,
		m_sd.BufferDesc.Width,
		m_sd.BufferDesc.Height, pBackBuffer);

	pBackBuffer->Release();


	m_DefaultCamera.SetViewMatrix();
	m_DefaultCamera.SetProjMatrix(D3DX_PI * 0.5f, 
		(float)m_rtClient.right/ (float)m_rtClient.bottom );

	m_pMainCamera = &m_DefaultCamera;


	m_dirAxis.Create(m_pd3dDevice,
		L"../../data/shader/shape.hlsl",
		L"../../data/eye.bmp");

	Init();
	return true;
}
HRESULT xCore::CreateDSV()
{
	HRESULT hr;
	ID3D11Texture2D* pTex = nullptr;
	D3D11_TEXTURE2D_DESC td;
	td.Width = g_rtClient.right;
	td.Height = g_rtClient.bottom;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&td, NULL, &pTex);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	dsvd.Texture2D.MipSlice = 0;
	hr = m_pd3dDevice->CreateDepthStencilView(
		pTex, &dsvd, &m_pDSV);

	if( pTex ) pTex->Release();
	
	return hr;
}
bool	xCore::GameFrame()
{	
	m_Timer.Frame();
	m_Input.Frame();
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
	ApplyRS(m_pContext, xDxState::g_pRSBackCullSolid);
	ApplySS(m_pContext, xDxState::g_pSSWrapLinear);

	m_pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	m_Timer.Release();
	m_Font.Release();
	m_Input.Release();
	m_dirAxis.Release();
	xDxState::Release();

	m_pSwapChain->SetFullscreenState(false, NULL);
	if (m_pDSV)m_pDSV->Release();
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pContext)m_pContext->Release();
	if (m_pDXGIFactory)m_pDXGIFactory->Release();
	m_pRenderTargetView = nullptr;
	m_pSwapChain = nullptr;
	m_pd3dDevice = nullptr;
	m_pContext = nullptr;
	m_pDXGIFactory = nullptr;
	return true;
}
xCore::xCore()
{
	m_pMainCamera = NULL;
}


xCore::~xCore()
{
}
