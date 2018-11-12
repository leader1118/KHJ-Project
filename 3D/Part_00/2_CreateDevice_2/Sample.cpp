#include "Sample.h"


bool Sample::Init()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIFactory()))
	{
		DXTRACE_MSG(DXGetErrorDescription(hr), hr);
		return false;
	}
	if (FAILED(hr = CreateDevice()))
	{
		DXTRACE_MSG(DXGetErrorDescription(hr));
		return false;
	}
	if (FAILED(hr = CreateSwapChain(m_hWnd, this->m_iWindowWidth, this->m_iWindowHeight)))
	{
		DXTRACE_MSG(DXGetErrorDescription(hr), hr);
		return false;
	}

	if (FAILED(hr = SetRenderTargetView()))
	{
		DXTRACE_MSG(DXGetErrorDescription(hr), hr);
	}
	if (FAILED(hr = SetViewPort()))
	{
		DXTRACE_MSG(DXGetErrorDescription(hr), hr);
		return false;
	}
	return true;
}
bool Sample::Render()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(m_hWnd, &m_rcWindowClient);

	float ClearColor[4] = { 0.0f,0.125f,0.3f,1.0f };//red,green,blue,alpha
	m_plmmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	m_pSwapChain->Present(0, 0);
	return true;

}
bool Sample::Release()
{
	if (!CleanupDevice())return false;
	return true;
}
Sample::Sample(void)
{

}
Sample::~Sample(void)
{

}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample gSample;
	if (!gSample.InitWindow(hInstance, nCmdShow, L"CreateDevice_1"))
	{
		MessageBox(0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();
	return 1;
}