#pragma once
#include "xShape.h"

struct xMapDesc
{
	int iNumCols;
	int iNumRows;
	int fDistance;
	float fScaleHeight;
	T_STR szTextureFile;
	T_STR szShaderFile;	
};
class xMap : public xBoxShape
{
public:
	xMapDesc m_xMapDesc;
	int m_iNumRows;
	int m_iNumCols;
	int m_iNumCellRows;
	int m_iNumCellCols;
	int m_iNumFace;
	int m_iNumVertices;
	float m_fCellDistance;
public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	D3DXVECTOR2		GetTextureOfVertex(float fU, float fV);
	D3DXVECTOR3		GetNormalOfVertex(int iIndex);
	D3DXVECTOR4		GetColorOfVertex(int iIndex);
	float			GetHeightOfVertex(int iIndex);
public:
	HRESULT LoadGeometryShader(T_STR szName) { return S_OK; };
public:
	bool	CreateMap(xMapDesc desc);
	bool    Load(ID3D11Device* pDevice, xMapDesc desc);
	bool	Init();
	bool	Frame();
	bool	Render(ID3D11DeviceContext* pContext);
	bool	Release();
public:
	xMap();
	virtual ~xMap();
};

