#include "DX_Device.h"
#include "DX_State.h"
#include "DX_Extern.h"

//DX11에대한 정보인거 같으니 번역해서 한번 볼것
//http://seanmiddleditch.com/direct3d-11-debug-api-tricks/

HRESULT		CDXDevice::CreateDevice()
{
	HRESULT hr = S_OK;
	UINT	CreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	//디버그시 포함 플레그
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//TYPE들이 전부 배열로 되있는 이유
	//버전체크를 위해서 제일 위의 목록부터
	//지원가능한것을 체크해 나간다
	//UNKOWN ==> 그래픽 카드 하드웨어가 어떤것인지 모를때 주로 사용하는 장치를 자동 지정
	//HARDWARE ==> 지금 지정되어있는 장치를 사용
	//WARP ==> 고성능 소프트웨어 레스터라이저 그냥 CPU가 GPU대신 고속 연산한다고 생각하면됨
	//REFERENCE ==> CPU사용
	D3D_DRIVER_TYPE		DriverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT				NumDriverTypes = sizeof(DriverTypes) / sizeof(DriverTypes[0]);

	//그래픽장치 하드웨어의 버전을 물어보는것
	//배열의 순서대로 물어본다
	D3D_FEATURE_LEVEL	pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT				NumFeatureTypes = sizeof(pFeatureLevels) / sizeof(pFeatureLevels[0]);

	//IDXGIAdapter ==> 그래픽 카드 장치를 의미
	IDXGIAdapter*		pAdapter;
	m_pGIFactory->EnumAdapters(0, &pAdapter);

	//위의 그래픽 카드 지원의 값 반환을 알아보기 위한 자료형
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
	//_ASSERT == 안정성 검사를 위한 매크로함수
	_ASSERT(m_pD3DDevice != NULL);
	_ASSERT(m_pGIFactory != NULL);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	//DX에서 출력할 창을 윈도우 메인 핸들을 통해 받아오는 작업
	SwapChainDesc.OutputWindow = m_hWnd;
	//윈도우의 변형을 허가해 줄것인지 아닌지
	SwapChainDesc.Windowed = TRUE;
	//윈도우의 가로 세로 값
	SwapChainDesc.BufferDesc.Width = WINCX;
	SwapChainDesc.BufferDesc.Height = WINCY;
	//화면 주사율 설정(ex.60hz)
	//Numerator ==> 화면 주사율의 분자
	//만약 114hz 화면 지원 모니터라면 바꿔주면 된다
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	//Denominator ==> 화면 주사율의 분모
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	//컬러값들을 RGBA를 8비트씩 사용하겠다 그냥 우리가 쓰던 컬러값을 사용하겠다
	//UNORM은 그냥 마이너스 값이 필요없으니까 정규화 안된 unsinged값을 사용하겠다
	//왜냐하면 컬러값이 0~255까지만 있으니까
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//오프스크린 버퍼의 사용 용도
	//선택의 여지가 없다 DXGI_USAGE_RENDER_TARGET_OUTPUT외의 것은 다른곳에서 사용
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//멀티 샘플링의 숫자를 말한다
	//여러번 뿌려주는것 ==> 계단현상방지
	SwapChainDesc.SampleDesc.Count = 1;
	//윈도우 모드에서 전체화면 모드로 전환하면 창의 크기에 맞게 화면 해상도가 변경된다
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = m_pGIFactory->CreateSwapChain(m_pD3DDevice,
		&SwapChainDesc, &m_pSwapChain);

	//윈도우 전체화면 true false
	//전체화면
	hr = m_pSwapChain->SetFullscreenState(false, NULL);
	return hr;
}

HRESULT		CDXDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	//생성된 스왑체인의 정보를 조회
	hr = m_pSwapChain->GetDesc(&m_SwapChainDesc);

	//렌더타겟 생성
	//__uuidof매크로 ==> DirectX112D에서 클래스네임 충돌이 안나게끔
	//하기 위해 유일한 값으로 인스턴트생성을 하겠다라는 뜻
	ID3D11Texture2D* pResource;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pResource);
	hr = m_pD3DDevice->CreateRenderTargetView(pResource, NULL, &m_pRTV);
	pResource->Release();

	if (SUCCEEDED(hr))
	{
		//OM의 뜻 Output-Merger Stage 나중에 렌더링 파이프 라인 도표를 보면 될것
		m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	}
	return hr;
}

HRESULT		CDXDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	//뷰포트 설정
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = float(m_SwapChainDesc.BufferDesc.Width);
	m_ViewPort.Height = float(m_SwapChainDesc.BufferDesc.Height);
	//화면의 깊이값
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
	//생성된 스왑체인의 정보를 조회
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

	//반드시 디바이스 생성시 어뎁터를 명시해야함
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
	//첫번째 인자값은 0일경우 즉시 시연되고 동기화된다(주사율을 지연안시키고 시연한다)
	//나머지 0이 아닌 1234값일 경우 지연되었다가 시연된다
	//두번째 인자값은 사용하지 않는다 다른 플레그 값은 게임이 아닌 그래픽 작업등에서 사용한다
	m_pSwapChain->Present(0, 0);

	return true;
}

bool		CDXDevice::Release()
{
	if (m_pDSV != NULL)					m_pDSV->Release();
	if (m_pRTV != NULL)					m_pDSV->Release();
	if (m_pImmediateContext != NULL)	m_pImmediateContext->Release();
	if (m_pD3DDevice != NULL)			m_pD3DDevice->Release();
	//잘모르겠으니 선생님 수업 잘들을것
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