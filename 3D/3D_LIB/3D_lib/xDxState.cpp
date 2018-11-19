#include "xDxState.h"


namespace DX
{
	ID3D11BlendState* xDxState::g_pBSNoBlend=0;
	ID3D11BlendState* xDxState::g_pBSAlphaBlend=0;

	ID3D11DepthStencilState*   xDxState::g_pDSVStateEnableLessEqual =0;
	ID3D11DepthStencilState*   xDxState::g_pDSVStateEnableGreater =0;

	ID3D11RasterizerState* xDxState::g_pRSWireFrame=0;
	ID3D11RasterizerState* xDxState::g_pRSSolid = 0;
	ID3D11RasterizerState* xDxState::g_pRSBackCullSolid = 0;
	ID3D11RasterizerState* xDxState::g_pRSFrontCullSolid = 0;
	ID3D11RasterizerState* xDxState::g_pRSNoneCullSolid = 0;
	ID3D11RasterizerState* xDxState::g_pRSBackCullWireFrame = 0;
	ID3D11RasterizerState* xDxState::g_pRSFrontCullWireFrame = 0;
	ID3D11RasterizerState* xDxState::g_pRSNoneCullWireFrame = 0;

	ID3D11SamplerState*	xDxState::g_pSSWrapLinear=NULL;

	HRESULT xDxState::SetState(ID3D11Device* pd3dDevice)
	{
		HRESULT hr;
		///////////////////////// blend //////////////
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		bd.RenderTarget[0].RenderTargetWriteMask = 
			D3D11_COLOR_WRITE_ENABLE_ALL;
		pd3dDevice->CreateBlendState(&bd, &g_pBSAlphaBlend);

		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		hr = pd3dDevice->CreateBlendState(&bd, &g_pBSNoBlend);

		/////////////////////////////
		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory(&dsd, sizeof(dsd));
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&g_pDSVStateEnableLessEqual);

		dsd.DepthEnable = TRUE;
		dsd.DepthFunc = D3D11_COMPARISON_GREATER;
		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&g_pDSVStateEnableGreater);
		////////////////////////////////


		//////////////////////////////////
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_BACK;
		rd.DepthClipEnable = TRUE;

		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSWireFrame);
		rd.FillMode = D3D11_FILL_SOLID;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSSolid);
		rd.CullMode = D3D11_CULL_FRONT;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSFrontCullSolid);
		rd.CullMode = D3D11_CULL_BACK;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSBackCullSolid);
		rd.CullMode = D3D11_CULL_NONE;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSNoneCullSolid);

		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_FRONT;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSFrontCullWireFrame);
		rd.CullMode = D3D11_CULL_BACK;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSBackCullWireFrame);
		rd.CullMode = D3D11_CULL_NONE;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&g_pRSNoneCullWireFrame);
		//////////////////////////////////
		
		D3D11_SAMPLER_DESC descSamp;
		descSamp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.MipLODBias = 0;
		descSamp.MaxAnisotropy = 16;
		descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		descSamp.ComparisonFunc = D3D11_COMPARISON_NEVER;

		descSamp.BorderColor[0] = 1.0f;
		descSamp.BorderColor[1] = 0.0f;
		descSamp.BorderColor[2] = 0.0f;
		descSamp.BorderColor[3] = 1.0f;
		descSamp.MinLOD = 0;
		descSamp.MaxLOD = D3D10_FLOAT32_MAX;
		pd3dDevice->CreateSamplerState(&descSamp,
			&g_pSSWrapLinear);
		
		
		return hr;
	}
	bool xDxState::Release()
	{
		if(g_pDSVStateEnableLessEqual)g_pDSVStateEnableLessEqual->Release();
		if(g_pDSVStateEnableGreater) g_pDSVStateEnableGreater->Release();
		if(g_pRSWireFrame) g_pRSWireFrame->Release();
		if(g_pRSSolid) g_pRSSolid->Release();
		if(g_pRSBackCullSolid) g_pRSBackCullSolid->Release();
		if(g_pRSFrontCullSolid) g_pRSFrontCullSolid->Release();
		if(g_pRSNoneCullSolid) g_pRSNoneCullSolid->Release();
		if(g_pRSBackCullWireFrame) g_pRSBackCullWireFrame->Release();
		if(g_pRSFrontCullWireFrame) g_pRSFrontCullWireFrame->Release();
		if(g_pRSNoneCullWireFrame) g_pRSNoneCullWireFrame->Release();
		if (g_pBSNoBlend) g_pBSNoBlend->Release();
		if (g_pBSAlphaBlend) g_pBSAlphaBlend->Release();
		if(g_pSSWrapLinear) g_pSSWrapLinear->Release();
		return true;
	}

	xDxState::xDxState()
	{
		
	}


	xDxState::~xDxState()
	{
	}
}
