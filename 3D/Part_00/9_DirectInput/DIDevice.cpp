#include "DIDevice.h"

HRESULT DIDevice::InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CreateDevice()))
	{
		MessageBox(0, _T("CreateDevice ����"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = CreateSwapChain(hWnd, iWidth, iHeight, IsFullScreen)))
	{
		MessageBox(0, _T("CreateSwapChain ����"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = SetRenderTargetView()))
	{
		MessageBox(0, _T("SetRenderTargetView ���� "), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = SetViewPort()))
	{
		MessageBox(0, _T("SetViewPort ���� "), _T("Fatal error"), MB_OK);
		return hr;
	}

	// ALT+ENTER Ű�� ���´�.
	if (FAILED(hr = m_pGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	{
		return hr;
	}
	return hr;
}

BOOL DIDevice::GetFullScreenFlag()
{
	return m_IsFullScreenMode;
}
void DIDevice::SetFullScreenFlag(BOOL bFlag)
{
	m_IsFullScreenMode = bFlag;
}
ID3D11Device* DIDevice::GetDevice()
{
	assert(m_pd3dDevice);
	return m_pd3dDevice;
}
ID3D11DeviceContext* DIDevice::GetContext()
{
	assert(m_plmmediateContext);
	return m_plmmediateContext;
}
IDXGISwapChain* DIDevice::GetSwapChain()
{
	assert(m_pSwapChain);
	return m_pSwapChain;
}
ID3D11RenderTargetView* DIDevice::GetRenderTargeView()
{
	assert(m_pRenderTargetView);
	return m_pRenderTargetView;
}
IDXGIFactory* DIDevice::GetGIFactory()
{
	assert(m_pGIFactory);
	return m_pGIFactory;
}
//NEW

HRESULT DIDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == NULL) return true;
	
	HRESULT hr;

	/////////////////////////////////////////////////////////
	// ���� Ÿ�ϰ� ���̽��ٽ� ���۸� �����Ѵ�.
	m_plmmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTargetView)m_pRenderTargetView->Release();

	///////////////////////////////////////////////////////////
	// ������� ũ�⸦ �����Ѵ�.
	///////////////////////////////////////////////////////////

	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, iWidth, iHeight, CurrentSD.BufferDesc.Format, CurrentSD.Flags);

	/*DXGI_MODE_DESC desc;
	ZeroMemory(&desc, sizeof (desc));
	desc.Width = iWidth;
	desc.Height = iHeight;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.RefreshRate.Denominator = 0;
	desc.RefreshRate.Numerator = 0;
	desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;*/
	// ������ ũ�� �� �ػ�( ȭ���� ) ����
	//m_pSwapChain->ResizeTarget(&desc);		

	//����Ÿ�Ϻ� ���� �� �����Ѵ�.
	if (FAILED(hr = SetRenderTargetView()))
	{
		return hr;
	}
	// ����Ʈ�� �����ϰ� �����Ѵ�.
	if (FAILED(hr = SetViewPort()))
	{
		return hr;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
// DXGIFactory �������̽��κ��� IDXGISwapChain �������̽��� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////

HRESULT DIDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr = S_OK;
	SetFullScreenFlag(IsFullScreen);
	if (m_pGIFactory == NULL) return S_FALSE;
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
	sd.Windowed = !m_IsFullScreenMode;
	// �߰�
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain)))
	{
		return hr;
	}
	return hr;
}

/////////////////////////////////////////////////////////
// ID3D11Device �������̽��� �����Ѵ�.
/////////////////////////////////////////////////////////

HRESULT DIDevice::CreateDevice()
{
	HRESULT hr;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevel);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		if (SUCCEEDED(hr = D3D11CreateDevice(NULL, m_driverType, NULL, createDeviceFlags,
			featureLevel, numFeatureLevels,
			D3D11_SDK_VERSION, &m_pd3dDevice, &m_FeatureLevel, &m_plmmediateContext)))
		{
			if (FAILED(hr) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if (m_plmmediateContext)m_plmmediateContext->Release();
				if (m_pd3dDevice)m_pd3dDevice->Release();
				continue;
			}
			break;
		}
	}
	if (FAILED(hr))return hr;
	

	return CreateGIFactory();
}
HRESULT DIDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL)return E_FAIL;
	HRESULT hr; //CreateDXGIFactory (__uuidof(IDXGIFactory),(void**)(&m_pGIFactory));
	IDXGIDevice* pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);

	IDXGIAdapter* pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDXGIAdapter);

	IDXGIFactory* pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return hr;
}
//---------------------------------------------------------------------
// DXGIFactory �������̽��κ��� IDXGISwapChain �������̽��� �����Ѵ�.
//---------------------------------------------------------------------

HRESULT DIDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	// Create a render target view
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

HRESULT DIDevice::SetViewPort()
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

bool DIDevice::CleanupDevice()
{
	// �ʱ� Ǯ��ũ�� �����쿡�� �������α׷��� ������ ��쿡�� ������ ��ȯ �Ŀ�
	// ��ü���� �Ҹ��ؾ��Ѵ�. (�޸� ������ ���� �� �ִ�.)
	m_pSwapChain->SetFullscreenState(false, NULL);

	if (m_plmmediateContext)m_plmmediateContext->Release();
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


DIDevice::DIDevice(void)
{
	m_driverType = D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_plmmediateContext = NULL;
	m_pGIFactory = NULL;
}


DIDevice::~DIDevice(void)
{
}
