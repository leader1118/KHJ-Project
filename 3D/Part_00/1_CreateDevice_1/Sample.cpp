#include "Sample.h"

// 디바이스 생성-1-
bool	Sample::Init()
{
	HRESULT hr;

	UINT createDeviceFlags = 0;
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

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_iWindowWidth;
	sd.BufferDesc.Height = m_iWindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		if (SUCCEEDED(hr = D3D11CreateDeviceAndSwapChain(
			NULL, m_DriverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd,
			&m_pSwapChain, &m_pd3dDevice, &m_FeatureLevel,
			&m_plmmediateContext)))
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
	if (FAILED(hr))
	{
		return true;
	}
	/////////////////////////
	// Create a Render target view
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) return false;

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))return false;

	m_plmmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	//////////////////////////////
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);
	// Setup the viewport
	m_ViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_ViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_ViewPort.MaxDepth = 0.0f;
	m_ViewPort.MinDepth = 1.0;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_plmmediateContext->RSSetViewports(1, &m_ViewPort);
	return true;
}
bool Sample::Render()
{
	// 백버퍼를 지운다.
	float clearColor[4] = { 0.0f,0.125f,0.3f,1.0f }; //red,green,blue,alpha
	m_plmmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pSwapChain->Present(0, 0);
	return true;
}
bool Sample::Release()
{
	if (m_plmmediateContext)m_plmmediateContext->ClearState();
	if (m_plmmediateContext)m_pRenderTargetView->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_plmmediateContext)m_plmmediateContext->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();

	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_plmmediateContext = NULL;
	return true;
}
Sample::Sample(void)
{
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_plmmediateContext = NULL;
}
Sample::~Sample(void)
{

}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample gSample;
	if (!gSample.InitWindow(hInstance, nCmdShow, L"CreateDevice_0"))
	{
		MessageBox(0, _T("Sample 초기화 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();
	return 1;
}