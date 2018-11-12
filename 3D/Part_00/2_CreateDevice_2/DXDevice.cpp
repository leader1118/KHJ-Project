#include "DXDevice.h"

// --------------------------------------------------------
// ID3D11Device 인터페이스를 생성한다.
// --------------------------------------------------------

HRESULT	DXDevice::CreateDevice()
{
	HRESULT hr;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

	//IDXGIAdapter* pAdapter = NULL;
	//m_pGIFactory->EnumAdapters(0,&pAdapter);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		if (SUCCEEDED(hr = D3D11CreateDevice(NULL, m_DriverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &m_pd3dDevice, &m_FeatureLevel, &m_plmmediateContext)))
		{
			if (FAILED(hr) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if (m_plmmediateContext) m_plmmediateContext->Release();
				if (m_pd3dDevice)m_pd3dDevice->Release();
				continue;
			}
			break;
		}
	}
	// if (pAdapter) pAdapter-> Relase();

	if (FAILED(hr))
	{
		//DXTRACE_ERR_MSGBOX(DXGetErrorDescription(hr),hr);
		return false;
	}
	DXTRACE_MSG(DXGetErrorDescription(hr));
	return S_OK;
}
// -----------------------------------------------
// DXGIFactory 인터페이스를 생성한다.
// -----------------------------------------------
HRESULT DXDevice::CreateGIFactory()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory))))
	{
		//DXTRACE_ERR_MSGBOX(DXGetErrorDescription(hr),hr);
		//MessageBox(m_hWnd,DXGetErrorDescription(hr),DXGetErrorString(hr),MB_OK);
		return false;
	}
	return hr;
}
// --------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
// --------------------------------------------------------------------

HRESULT DXDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	if (m_pGIFactory == NULL)return S_FALSE;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = iWidth;
	sd.BufferDesc.Height = iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain)))
	{
		return hr;
	}
	return hr;
}
HRESULT DXDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	//Create a render target view
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	m_plmmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	return S_OK;
}
HRESULT DXDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);
	// Setup the viewport
	m_ViewPort.Width = Desc.BufferDesc.Width;
	m_ViewPort.Height = Desc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_plmmediateContext->RSSetViewports(1, &m_ViewPort);
	return S_OK;
}
bool DXDevice::CleanupDevice()
{
	if (m_plmmediateContext)m_plmmediateContext->ClearState();
	if (m_pRenderTargetView)m_pRenderTargetView->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_plmmediateContext)m_plmmediateContext->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pGIFactory)m_pGIFactory->Release();

	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_plmmediateContext = NULL;
	m_pGIFactory = NULL;
	return true;
}
DXDevice::DXDevice()
{
	m_driverType = D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_pSwapChain = NULL;
	m_pd3dDevice = NULL;
	m_pRenderTargetView = NULL;
	m_plmmediateContext = NULL;
}


DXDevice::~DXDevice()
{
}
