#pragma once

#include "MyWindow.h"

class CDXDevice
	: public CMyWindow
{
private:
	//�׷��� ī�� ��ġ �������̽�(���ҽ�����)
	ID3D11Device*				m_pD3DDevice;
	//��� ����, ���� �� ���� �������̽�
	ID3D11DeviceContext*		m_pImmediateContext;
public:
	ID3D11Debug*				m_pDebug;
	IDXGIFactory*				m_pGIFactory;
	//������ũ�� (������۸� ���)�������̽�
	IDXGISwapChain*				m_pSwapChain;
	//������ũ�� ��� ����
	ID3D11RenderTargetView*		m_pRTV;
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;
	D3D11_VIEWPORT				m_ViewPort;
	D3D_DRIVER_TYPE				m_DriverType;
	//���ٽ� ����
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