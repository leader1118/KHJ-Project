#pragma once

#include "MyWindow.h"

class CDXDevice
	: public CMyWindow
{
private:
	//그래픽 카드 장치 인터페이스(리소스생성)
	ID3D11Device*				m_pD3DDevice;
	//명령 제어, 전달 및 실행 인터페이스
	ID3D11DeviceContext*		m_pImmediateContext;
public:
	ID3D11Debug*				m_pDebug;
	IDXGIFactory*				m_pGIFactory;
	//오프스크린 (더블버퍼링 담당)인터페이스
	IDXGISwapChain*				m_pSwapChain;
	//오프스크린 대상 버퍼
	ID3D11RenderTargetView*		m_pRTV;
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;
	D3D11_VIEWPORT				m_ViewPort;
	D3D_DRIVER_TYPE				m_DriverType;
	//스텐실 버퍼
	ID3D11DepthStencilView*		m_pDSV;
public:
	ID3D11Device*			GetDevice()		{ return m_pD3DDevice; };
	ID3D11DeviceContext*	GetContext()	{ return m_pImmediateContext; };
public:
	bool					Init();
	bool					PreRender();
	bool					PostRender();
	bool					Release();
public:
	bool					Reset(UINT iWidth, UINT iHeight);
	HRESULT					CreateGIFactory();
	HRESULT					CreateDevice();
	HRESULT					CreateSwapChain();
	HRESULT					CreateDepthStencilState();
	HRESULT					SetRenderTargetView();
	HRESULT					SetViewPort();
public:
	CDXDevice();
	virtual ~CDXDevice();
};