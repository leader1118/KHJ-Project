#include "DX_Device.h"
#include "DX_State.h"
#include "DX_Extern.h"

//DX11������ �����ΰ� ������ �����ؼ� �ѹ� ����
//http://seanmiddleditch.com/direct3d-11-debug-api-tricks/

HRESULT		CDXDevice::CreateDevice()
{
	HRESULT hr = S_OK;
	UINT	CreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	//����׽� ���� �÷���
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//TYPE���� ���� �迭�� ���ִ� ����
	//����üũ�� ���ؼ� ���� ���� ��Ϻ���
	//���������Ѱ��� üũ�� ������
	//UNKOWN ==> �׷��� ī�� �ϵ��� ������� �𸦶� �ַ� ����ϴ� ��ġ�� �ڵ� ����
	//HARDWARE ==> ���� �����Ǿ��ִ� ��ġ�� ���
	//WARP ==> ���� ����Ʈ���� �����Ͷ����� �׳� CPU�� GPU��� ��� �����Ѵٰ� �����ϸ��
	//REFERENCE ==> CPU���
	D3D_DRIVER_TYPE		DriverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT				NumDriverTypes = sizeof(DriverTypes) / sizeof(DriverTypes[0]);

	//�׷�����ġ �ϵ������ ������ ����°�
	//�迭�� ������� �����
	D3D_FEATURE_LEVEL	pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT				NumFeatureTypes = sizeof(pFeatureLevels) / sizeof(pFeatureLevels[0]);

	//IDXGIAdapter ==> �׷��� ī�� ��ġ�� �ǹ�
	IDXGIAdapter*		pAdapter;
	m_pGIFactory->EnumAdapters(0, &pAdapter);

	//���� �׷��� ī�� ������ �� ��ȯ�� �˾ƺ��� ���� �ڷ���
	D3D_FEATURE_LEVEL	retFeatureLevel;

	for (unsigned int i = 0; i < NumDriverTypes; i++)
	{
		m_DriverType = DriverTypes[i];
		if (SUCCEEDED(hr = D3D11CreateDevice(
									pAdapter, m_DriverType, NULL,
									CreateDeviceFlags, pFeatureLevels, NumFeatureTypes,
									D3D11_SDK_VERSION,
									&m_pD3DDevice, &retFeatureLevel, &m_pImmediateContext)))
		{
			if (retFeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if (m_pImmediateContext)
					m_pImmediateContext->Release();
				if (m_pD3DDevice)
					m_pD3DDevice->Release();
				continue;
			}
			break;
		}
	}

	hr = m_pD3DDevice->QueryInterface(IID_PPV_ARGS(&m_pDebug));
	return hr;
}

HRESULT		CDXDevice::CreateGIFactory()
{
	HRESULT hr;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
		(void**)(&m_pGIFactory));

	return hr;
}

HRESULT		CDXDevice::CreateSwapChain()
{
	HRESULT hr = S_OK;
	//_ASSERT == ������ �˻縦 ���� ��ũ���Լ�
	_ASSERT(m_pD3DDevice != NULL);
	_ASSERT(m_pGIFactory != NULL);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	//DX���� ����� â�� ������ ���� �ڵ��� ���� �޾ƿ��� �۾�
	SwapChainDesc.OutputWindow = m_hWnd;
	//�������� ������ �㰡�� �ٰ����� �ƴ���
	SwapChainDesc.Windowed = TRUE;
	//�������� ���� ���� ��
	SwapChainDesc.BufferDesc.Width = WINCX;
	SwapChainDesc.BufferDesc.Height = WINCY;
	//ȭ�� �ֻ��� ����(ex.60hz)
	//Numerator ==> ȭ�� �ֻ����� ����
	//���� 114hz ȭ�� ���� ����Ͷ�� �ٲ��ָ� �ȴ�
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	//Denominator ==> ȭ�� �ֻ����� �и�
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	//�÷������� RGBA�� 8��Ʈ�� ����ϰڴ� �׳� �츮�� ���� �÷����� ����ϰڴ�
	//UNORM�� �׳� ���̳ʽ� ���� �ʿ�����ϱ� ����ȭ �ȵ� unsinged���� ����ϰڴ�
	//�ֳ��ϸ� �÷����� 0~255������ �����ϱ�
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//������ũ�� ������ ��� �뵵
	//������ ������ ���� DXGI_USAGE_RENDER_TARGET_OUTPUT���� ���� �ٸ������� ���
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//��Ƽ ���ø��� ���ڸ� ���Ѵ�
	//������ �ѷ��ִ°� ==> ����������
	SwapChainDesc.SampleDesc.Count = 1;
	//������ ��忡�� ��üȭ�� ���� ��ȯ�ϸ� â�� ũ�⿡ �°� ȭ�� �ػ󵵰� ����ȴ�
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = m_pGIFactory->CreateSwapChain(m_pD3DDevice,
		&SwapChainDesc, &m_pSwapChain);

	//������ ��üȭ�� true false
	//��üȭ��
	hr = m_pSwapChain->SetFullscreenState(false, NULL);
	return hr;
}

HRESULT		CDXDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	//������ ����ü���� ������ ��ȸ
	hr = m_pSwapChain->GetDesc(&m_SwapChainDesc);

	//����Ÿ�� ����
	//__uuidof��ũ�� ==> DirectX112D���� Ŭ�������� �浹�� �ȳ��Բ�
	//�ϱ� ���� ������ ������ �ν���Ʈ������ �ϰڴٶ�� ��
	ID3D11Texture2D* pResource;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pResource);
	hr = m_pD3DDevice->CreateRenderTargetView(pResource, NULL, &m_pRTV);
	pResource->Release();

	if (SUCCEEDED(hr))
	{
		//OM�� �� Output-Merger Stage ���߿� ������ ������ ���� ��ǥ�� ���� �ɰ�
		m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	}
	return hr;
}

HRESULT		CDXDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	//����Ʈ ����
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = float(m_SwapChainDesc.BufferDesc.Width);
	m_ViewPort.Height = float(m_SwapChainDesc.BufferDesc.Height);
	//ȭ���� ���̰�
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;

	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
	return hr;
}

bool		CDXDevice::Reset(UINT iWidth, UINT iHeight)
{
	if (m_pD3DDevice == NULL)
		return true;

	HRESULT hr = S_OK;
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	
	if (m_pDSV != NULL)
		m_pDSV->Release();
	if (m_pRTV != NULL)
		m_pRTV->Release();

	if (FAILED(hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount,
		iWidth, iHeight, m_SwapChainDesc.BufferDesc.Format,
		m_SwapChainDesc.Flags)))
	{
		return false;
	}

	CreateDepthStencilState();
	if (FAILED(hr = SetRenderTargetView()))
		return false;
	if (FAILED(hr = SetViewPort()))
		return false;

	CMyWindow::ResizeClient(iWidth, iHeight);

	return true;
}

HRESULT		CDXDevice::CreateDepthStencilState()
{
	HRESULT hr = S_OK;
	//������ ����ü���� ������ ��ȸ
	hr = m_pSwapChain->GetDesc(&m_SwapChainDesc);

	ID3D11Texture2D* pTex;
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Width		= m_SwapChainDesc.BufferDesc.Width;
	texDesc.Height		= m_SwapChainDesc.BufferDesc.Height;
	texDesc.MipLevels	= 1;
	texDesc.ArraySize	= 1;
	texDesc.Format		= DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.SampleDesc.Count	= 1;
	texDesc.SampleDesc.Quality	= 0;
	texDesc.Usage			= D3D11_USAGE_DEFAULT;
	texDesc.BindFlags		= D3D11_BIND_DEPTH_STENCIL;
	texDesc.CPUAccessFlags	= 0;
	texDesc.MiscFlags		= 0;

	if (FAILED(hr = GetDevice()->CreateTexture2D(&texDesc, NULL, &pTex)))
	{
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format			= texDesc.Format;
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2D;

	if (FAILED(hr = GetDevice()->CreateDepthStencilView(pTex, &dsvd, &m_pDSV)))
	{
		return hr;
	}

	SAFE_RELEASE(pTex);

	return hr;
}

bool		CDXDevice::Init()
{
	HRESULT hr;
	if (FAILED(CreateGIFactory()))			{ return false; }
	if (FAILED(CreateDevice()))				{ return false; }
	if (FAILED(CreateSwapChain()))			{ return false; }
	if (FAILED(CreateDepthStencilState()))	{ return false; }
	if (FAILED(SetRenderTargetView()))		{ return false; }
	if (FAILED(SetViewPort()))				{ return false; }

	//�ݵ�� ����̽� ������ ��͸� ����ؾ���
	if (FAILED(hr = m_pGIFactory->MakeWindowAssociation(m_hWnd,
		DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	{
		return hr;
	}

	return true;
}

bool		CDXDevice::PreRender()
{
	float fRed = 0.0f;
	fRed = (cosf(g_fAccumulation) * 0.5f + 0.5f);
	float fGreen = 0.0f;
	fGreen = (sinf(g_fAccumulation) * 0.5f + 0.5f);

	float clearColor[4] = { 0.f, 0.f, 1.f, 1 };
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, (UINT8)0.0f);
	return true;
}

bool		CDXDevice::PostRender()
{
	//ù��° ���ڰ��� 0�ϰ�� ��� �ÿ��ǰ� ����ȭ�ȴ�(�ֻ����� �����Ƚ�Ű�� �ÿ��Ѵ�)
	//������ 0�� �ƴ� 1234���� ��� �����Ǿ��ٰ� �ÿ��ȴ�
	//�ι�° ���ڰ��� ������� �ʴ´� �ٸ� �÷��� ���� ������ �ƴ� �׷��� �۾���� ����Ѵ�
	m_pSwapChain->Present(0, 0);

	return true;
}

bool		CDXDevice::Release()
{
	if (m_pDSV != NULL)					m_pDSV->Release();
	if (m_pRTV != NULL)					m_pDSV->Release();
	if (m_pImmediateContext != NULL)	m_pImmediateContext->Release();
	if (m_pD3DDevice != NULL)			m_pD3DDevice->Release();
	//�߸𸣰����� ������ ���� �ߵ�����
	//m_pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	if (m_pDebug != NULL)				m_pDebug->Release();

	return true;
}

CDXDevice::CDXDevice()
{
	m_pRTV = NULL;
	m_pSwapChain = NULL;
	m_pImmediateContext = NULL;
	m_pD3DDevice = NULL;
}

CDXDevice::~CDXDevice()
{

}