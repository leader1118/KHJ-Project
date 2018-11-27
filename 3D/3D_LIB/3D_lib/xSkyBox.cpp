#include "xSkyBox.h"

bool  xSkyBox::Create(ID3D11Device* pDevice,
	T_STR  szShaderName,
	T_STR  szTextureName)
{
	D3DXMatrixScaling(&m_matWorld, 100.0f, 100.0f, 100.0f);
	xShape::Create(pDevice, szShaderName, szTextureName);
	return true;
}
HRESULT xSkyBox::LoadTexture(T_STR  szName)
{
	HRESULT hr = S_OK;

	TCHAR* g_szSkyTextures[] =
	{
		L"../../Include/data/st00_cm_front.bmp",
		L"../../Include/data/st00_cm_back.bmp",
		L"../../Include/data/st00_cm_right.bmp",
		L"../../Include/data/st00_cm_left.bmp",
		L"../../Include/data/st00_cm_up.bmp",
		L"../../Inckude/data/st00_cm_down.bmp"
	};
	int iNumTexture = sizeof(g_szSkyTextures) / sizeof(g_szSkyTextures[0]);

	for (int iTex = 0; iTex < iNumTexture; iTex++)
	{
		m_pTexSRV[iTex].Attach(DX::CreateShaderResourceView(m_pd3dDevice, g_szSkyTextures[iTex]));
	}

	return hr;
}
bool xSkyBox::Render(ID3D11DeviceContext* pContext)
{
	ApplySS(pContext, xDxState::g_pSSWrapPoint);
	//ApplyDSS(pContext, xDxState::g_pDSVStateDetphWriteDisable);

	D3DXMATRIX matView = m_matView;
	matView._41 = 0;
	matView._42 = 0;
	matView._43 = 0;
	SetMatrix(&m_matWorld, &matView, &m_matProj);

	pContext->UpdateSubresource(m_dxObj.m_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
	pContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	PreRender(pContext);
	//--------------------------------------------------------------------------------------
	// 한장씩 랜더링 하는 방법
	//--------------------------------------------------------------------------------------
	for (int iTex = 0; iTex < MAX_SKYBOX_TEXTURE; iTex++)
	{
		if (m_pTexSRV[iTex] == nullptr) break;
		pContext->PSSetShaderResources(0, 1, m_pTexSRV[iTex].GetAddressOf());
		// 랜더링에 사용할 인덱스 버퍼 갯수, 인덱스 버퍼 시작, 버텍스 버퍼 시작
		pContext->DrawIndexed(6, 6 * iTex, 0);
	}

	ApplySS(pContext, xDxState::g_pSSWrapLinear);
	//ApplyDSS(pContext, xDxState::g_pDSVStateEnableLessEqual);
	return true;
}
bool xSkyBox::Release()
{
	xShape::Release();
	return true;
}
xSkyBox::xSkyBox()
{
}


xSkyBox::~xSkyBox()
{
}
