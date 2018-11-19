#include "xShape.h"
void    xShape::SetColor(D3DXVECTOR4 vColor)
{
	m_cbData.vColor = vColor;
}

void  xShape::SetMatrix(
	D3DXMATRIX* pWorld,
	D3DXMATRIX* pView,
	D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}

	m_vPosition.x = m_matWorld._41;
	m_vPosition.y = m_matWorld._42;
	m_vPosition.z = m_matWorld._43;
	m_vLook.x = m_matWorld._11;
	m_vLook.y = m_matWorld._12;
	m_vLook.z = m_matWorld._13;
	m_vSide.x = m_matWorld._21;
	m_vSide.y = m_matWorld._22;
	m_vSide.z = m_matWorld._23;
	m_vUp.x = m_matWorld._31;
	m_vUp.y = m_matWorld._32;
	m_vUp.z = m_matWorld._33;

	D3DXMatrixTranspose(&m_cbData.matWorld,
		&m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView,
		&m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj,
		&m_matProj);
}
bool  xShape::Create(
	ID3D11Device* pDevice,
	T_STR  szShaderName,
	T_STR  szTextureName)
{
	m_pd3dDevice = pDevice;
	CreateVertexData();
	CreateIndexData();
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateConstantBuffer();
	
	LoadVertexShader(szShaderName);
	LoadPixelShader(szShaderName);
	LoadGeometryShader(szShaderName);

	CreateInputLayout();
	LoadTexture(szTextureName);
	return true;
}
HRESULT xShape::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_iVertexSize = sizeof(PNCT_VERTEX);
	DX::CreateVertexBuffer(m_pd3dDevice,
		m_iNumVertex,
		sizeof(PNCT_VERTEX),
		&m_VertexList.at(0),
		m_dxObj.m_pVertexBuffer.GetAddressOf());
	return hr;
}
HRESULT xShape::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	DX::CreateIndexBuffer(m_pd3dDevice,
		m_iNumIndex,
		sizeof(DWORD),
		&m_IndexList.at(0), 
		m_dxObj.m_pIndexBuffer.GetAddressOf());
	return hr;
}
HRESULT xShape::CreateConstantBuffer() {
	HRESULT hr = S_OK;
	DX::CreateConstantBuffer(m_pd3dDevice,
		1,
		sizeof(T_CB_DATA),
		m_dxObj.m_pConstantBuffer.GetAddressOf(),
		&m_cbData, false);
	return hr;
}
HRESULT xShape::CreateInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
			 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	DX::CreateInputLayout(m_pd3dDevice,
		m_dxObj.m_pVSBlob->GetBufferSize(),
		m_dxObj.m_pVSBlob->GetBufferPointer(),
		layout, numElements,
		m_dxObj.m_pInputLayout.GetAddressOf());

	return hr;
}
HRESULT xShape::LoadVertexShader(T_STR  szName) {
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexShader.Attach(
		DX::LoadVertexShaderFile(m_pd3dDevice, 
			szName.c_str(),
			m_dxObj.m_pVSBlob.GetAddressOf()));
	return hr;
}
HRESULT xShape::LoadPixelShader(T_STR  szName) {
	HRESULT hr = S_OK;
	m_dxObj.m_pPixelShader.Attach(
		DX::LoadPixelShaderFile(m_pd3dDevice,
			szName.c_str()));

	return hr;
}
HRESULT xShape::LoadGeometryShader(T_STR  szName) {
	HRESULT hr = S_OK;
	m_dxObj.m_pGeometryShader.Attach(
		DX::LoadGeometryShaderFile(m_pd3dDevice,
			szName.c_str()));

	return hr;
}
HRESULT xShape::LoadTexture(T_STR  szName) {
	HRESULT hr = S_OK;
	D3DX11_IMAGE_LOAD_INFO loadinfo;
	ZeroMemory(&loadinfo, sizeof(loadinfo));
	loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadinfo.Format = DXGI_FORMAT_FROM_FILE;
	ID3D11ShaderResourceView* pTex = NULL;
	hr=D3DX11CreateShaderResourceViewFromFile(
		m_pd3dDevice,
		szName.c_str(),
		&loadinfo, NULL, 
		m_dxObj.m_pTextureRV.GetAddressOf(), NULL);
	
	return hr;
}
bool  xShape::PreRender(
	ID3D11DeviceContext* pContext)
{
	m_dxObj.PreRender(pContext, m_iVertexSize);
	return true;
}
bool  xShape::Render(ID3D11DeviceContext* pContext) {
	pContext->UpdateSubresource(
		m_dxObj.m_pConstantBuffer.Get(),
		0, NULL, &m_cbData, 0, 0);
	pContext->IASetPrimitiveTopology(
		(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	m_dxObj.PreRender(pContext, m_iVertexSize);
	m_dxObj.PostRender(pContext, m_iVertexSize, m_iNumIndex);
	return true;
}
bool  xShape::PostRender(ID3D11DeviceContext* pContext	)
{
	m_dxObj.PostRender(pContext, m_iVertexSize, m_iNumIndex);
	return true;
}
bool  xShape::Release()
{
	return true;
}
bool  xShape::Frame()
{
	return true;
}
bool  xShape::Init()
{
	return true;
}
xShape::xShape()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_vPosition.x = m_matWorld._41;
	m_vPosition.y = m_matWorld._42;
	m_vPosition.z = m_matWorld._43;
	m_vLook.x = m_matWorld._11;
	m_vLook.y = m_matWorld._12;
	m_vLook.z = m_matWorld._13;
	m_vSide.x = m_matWorld._21;
	m_vSide.y = m_matWorld._22;
	m_vSide.z = m_matWorld._23;
	m_vUp.x = m_matWorld._31;
	m_vUp.y = m_matWorld._32;
	m_vUp.z = m_matWorld._33;

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


xShape::~xShape()
{
}


//////////////// TBoxSahpe //////////////////
HRESULT xBoxShape::CreateVertexData()
{
	HRESULT hr = S_OK;
	// ¾Õ¸é
	m_VertexList.resize(24);
	m_VertexList[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	// µÞ¸é
	m_VertexList[4] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[6] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[7] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[8] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[9] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[10] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[11] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿ÞÂÊ
	m_VertexList[12] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[13] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[14] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[15] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// À­¸é
	m_VertexList[16] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[17] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[18] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[19] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¾Æ·§¸é
	m_VertexList[20] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[21] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[22] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[23] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	m_iNumVertex = m_VertexList.size();
	return hr;
}
HRESULT xBoxShape::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

	m_iNumIndex = m_IndexList.size();	
	return hr;
}
xBoxShape::xBoxShape()
{
}


xBoxShape::~xBoxShape()
{
}