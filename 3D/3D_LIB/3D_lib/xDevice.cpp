#include "xDevice.h"
void xDevice::DeleteDeviceResources(){}
HRESULT xDevice::CreateDeviceResources(UINT width, UINT height) 
{
	return S_OK;
}
void xDevice::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice == NULL) return;
	m_pContext->OMSetRenderTargets(0, NULL, NULL);
	DeleteDeviceResources();
	m_pRenderTargetView->Release();

	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC sd = m_sd;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Width = width;
	hr = m_pSwapChain->ResizeBuffers(sd.BufferCount,
		width, height, sd.BufferDesc.Format,
		sd.Flags);
	if (SUCCEEDED(hr))
	{
		m_pSwapChain->GetDesc(&m_sd);
	}
	SetRenderTargetView();
	SetViewPort();

	CreateDeviceResources(width, height);
}
bool   xDevice::Init()
{
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

	m_pDXGIFactory->MakeWindowAssociation(g_hWnd,
		DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);
}
HRESULT xDevice::CreateDevice()
{
	HRESULT hr = S_OK;
	//1)디바이스 생성
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT FeatureLevels = 2;

	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE DriverType[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(DriverType) /
		sizeof(DriverType[0]);

	for (int iMode = 0; iMode < numDriverTypes; iMode++)
	{
		D3D_FEATURE_LEVEL retFL;

		if (SUCCEEDED(D3D11CreateDevice(
			NULL, DriverType[iMode],
			NULL, Flags,
			pFeatureLevels,
			FeatureLevels,
			D3D11_SDK_VERSION,
			&m_pd3dDevice,
			&retFL,
			&m_pContext)))
		{
			if (retFL != D3D_FEATURE_LEVEL_11_0)
			{
				if (m_pSwapChain)m_pSwapChain->Release();
				if (m_pd3dDevice)m_pd3dDevice->Release();
				if (m_pContext)m_pContext->Release();
				continue;
			}
			break;
		}
	}
	return hr;
}
HRESULT xDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;// = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory) );
	IDXGIDevice * pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pDXGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return hr;
}
HRESULT xDevice::CreateSwapChain()
{
	HRESULT hr = S_OK;

	ZeroMemory(&m_sd, sizeof(m_sd));
	m_sd.BufferDesc.Width = g_rtClient.right;
	m_sd.BufferDesc.Height = g_rtClient.bottom;
	m_sd.BufferDesc.RefreshRate.Numerator = 60;
	m_sd.BufferDesc.RefreshRate.Denominator = 1;
	m_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_sd.BufferCount = 1;
	m_sd.OutputWindow = g_hWnd;
	m_sd.Windowed = true;
	m_sd.SampleDesc.Count = 1;
	m_sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = m_pDXGIFactory->CreateSwapChain(
		m_pd3dDevice, &m_sd, &m_pSwapChain)))
	{
		return false;
	}
	return hr;
}
HRESULT xDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	// 2)랜더타켓 뷰 생성
	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		(void**)&pBackBuffer);
	m_pd3dDevice->CreateRenderTargetView(
		pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	return hr;
}
void xDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	// 3)뷰포트 생성
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = m_sd.BufferDesc.Width;
	vp.Height = m_sd.BufferDesc.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pContext->RSSetViewports(1, &vp);

	g_rtClient.right = m_sd.BufferDesc.Width;
	g_rtClient.bottom = m_sd.BufferDesc.Height;
}
HRESULT xDevice::CreateDSV()
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

	if (pTex) pTex->Release();

	return hr;
}
bool	xDevice::Release()
{
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
xDevice::xDevice()
{
}


xDevice::~xDevice()
{
}
