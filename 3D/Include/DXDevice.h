#pragma once
#include "DUtils.h"

class DXDevice
{
public:
	// ----------------------------------------------------
	// Global Variables
	// ----------------------------------------------------
	ID3D11Device*			m_pd3dDevice;			// 디바이스 객체
	IDXGISwapChain*			m_pSwapChain;			// 스왑체인 객체
	ID3D11RenderTargetView*	m_pRenderTargetView;	// 메인 랜더타켓 뷰
	D3D11_VIEWPORT			m_ViewPort;				// 뷰 포트
	D3D_DRIVER_TYPE			m_driverType;			// 디바이스 타입(디폴트 : 하드웨어 가속)
	IDXGIFactory*			m_pGIFactory;			// DXGI 객체
	ID3D11DeviceContext*	m_plmmediateContext;	// 디바이스 컨텍스트
	D3D_DRIVER_TYPE			m_DriverType;			// 디바이스 타입
	D3D_FEATURE_LEVEL		m_FeatureLevel;			// Directx의 기능 수준
	
public:
	//-------------------------------------------------
	// 디바이스 및 스왑체인 생성 :
	// 1, CreateDevice()
	// 2, CreateGIFactory()
	// 3, CreateSwapChain()
	// 4, SetRenderTargetView()
	// 5, SetViewPort()
	//--------------------------------------------------

	HRESULT			CreateDevice();
	HRESULT			CreateGIFactory();
	HRESULT			CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh);
	// -------------------------------------------------
	//
	// -------------------------------------------------
	HRESULT			SetRenderTargetView();
	HRESULT			SetViewPort();
	bool			CleanupDevice();
public:
	DXDevice();
	virtual ~DXDevice();
};

