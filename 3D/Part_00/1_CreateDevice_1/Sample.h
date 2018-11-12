#pragma once
#include "DUtils.h"
#include "DXWindow.h"

class Sample : public DXWindow
{
private:
	//--------------------------------------
	// GlobalVariables
	//--------------------------------------
	ID3D11Device*			m_pd3dDevice; // ����̽� ��ü
	ID3D11DeviceContext*	m_plmmediateContext; // ����̽� ���ؽ�Ʈ ��ü
	IDXGISwapChain*			m_pSwapChain;		// ����ü�� ��ü
	ID3D11RenderTargetView* m_pRenderTargetView; // ���� ����Ÿ�� �� ��ü

	D3D_DRIVER_TYPE			m_DriverType;		// ����̽� Ÿ�� �Ӽ���
	D3D_FEATURE_LEVEL		m_FeatureLevel;		// Direct3D Ư������ �Ӽ���
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// ����ü�� �Ӽ���
	D3D11_VIEWPORT			m_ViewPort;			// �� ��Ʈ �Ӽ���
public:
	bool	Init();
	bool	Render();
	bool	Release();
public:
	Sample(void);
	~Sample(void);
};
