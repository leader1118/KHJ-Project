#pragma once
#include "xObjectStd.h"
#include "xDxState.h"
class xShape
{
public:
	ID3D11Device* m_pd3dDevice;
	D3D_PRIMITIVE_TOPOLOGY m_Primitive;
	xDxObj  m_dxObj;
	vector<PNCT_VERTEX>  m_VertexList;
	vector<DWORD>		 m_IndexList;
	UINT				 m_iVertexSize;
	T_CB_DATA            m_cbData;
	D3DXMATRIX			 m_matWorld;
	D3DXMATRIX			 m_matView;
	D3DXMATRIX			 m_matProj;
	D3DXVECTOR3			 m_vPosition;
	D3DXVECTOR3			 m_vLook;
	D3DXVECTOR3			 m_vSide;
	D3DXVECTOR3			 m_vUp;

	UINT    m_iNumIndex;
	UINT    m_iNumVertex;
public:
	void    SetColor(D3DXVECTOR4 vColor);
public:
	bool  Create(ID3D11Device* pDevice,
		T_STR  szShaderName,
		T_STR  szTextureName);
	virtual HRESULT CreateVertexData() {
		return S_OK;
	};
	virtual HRESULT CreateIndexData() {
		return S_OK;
	};
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT CreateInputLayout();
	virtual HRESULT LoadVertexShader(T_STR  szName);
	virtual HRESULT LoadPixelShader(T_STR  szName);
	virtual HRESULT LoadGeometryShader(T_STR  szName);
	virtual HRESULT LoadTexture(T_STR  szName);
	virtual bool  PreRender(ID3D11DeviceContext* pContext);
	virtual void  SetMatrix(D3DXMATRIX* pWorld = NULL, D3DXMATRIX* pView = NULL, D3DXMATRIX* pProj = NULL);
	virtual bool  Render(ID3D11DeviceContext* pContext);
	virtual bool  PostRender(ID3D11DeviceContext* pContext);
	virtual bool  Release();
	virtual bool  Frame();
	virtual bool  Init();
public:
	xShape();
	virtual ~xShape();
};

class xBoxShape : public xShape
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	HRESULT LoadGeometryShader(T_STR  szName) {
		return S_OK;
	};
public:
	xBoxShape();
	virtual ~xBoxShape();
};
class xPlaneShape : public xShape
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	HRESULT LoadGeometryShader(T_STR  szName) {
		return S_OK;
	};
public:
	xPlaneShape();
	virtual ~xPlaneShape();
};
class xLineShape : public xShape
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	HRESULT LoadGeometryShader(T_STR  szName) {
		return S_OK;
	};
	bool Draw(
		ID3D11DeviceContext* pContext,
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd,
		D3DXVECTOR4 vColor = D3DXVECTOR4(1,0,0,1));
	HRESULT LoadPixelShader(T_STR  szName);
public:
	xLineShape();
	virtual ~xLineShape();
};
class xDirLineShape : public xLineShape
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	HRESULT LoadGeometryShader(T_STR  szName) {
		return S_OK;
	};
	bool Render(ID3D11DeviceContext* pContext);
public:
	xDirLineShape();
	virtual ~xDirLineShape();
};
class xSphereShape : public xBoxShape
{
public:
	HRESULT LoadVertexShader(T_STR  szName);
	HRESULT LoadGeometryShader(T_STR  szName);
public:
	xSphereShape();
	virtual ~xSphereShape();
};