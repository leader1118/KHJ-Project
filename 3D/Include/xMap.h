#pragma once
#include "xStd.h"
#include "xShape.h"
struct xMapDesc
{
	int iNumCols; // 가로 개수
	int iNumRows; // 세로 개수
	float fDistance;
	float fScaleHeight;
	T_STR szTextureFile;
	T_STR szShaderFile;
};
class xMap : public xBoxShape
{
public:
	xMapDesc m_xMapDesc;
public:
	int		m_iNumRows;
	int		m_iNumCols;
	int		m_iNumCellRows;
	int		m_iNumCellCols;
	int		m_iNumFace;
	int		m_iNumVertices;
	float	m_fColliDistance;
public:
	bool CreateMap(xMapDesc desc);
	bool Load(ID3D11Device* pDevice, xMapDesc desc);
	bool CreateHeightMap(ID3D11Device* pDevice,T_STR szName);
	bool Init();
	bool Frame();
	bool Release();
	bool Render(ID3D11DeviceContext* pContext);
public:
	D3DXVECTOR2 GetTextureOfVertex(float fU, float fV);
	D3DXVECTOR3 GetNormalOfVertex(int iIndex);
	D3DXVECTOR4 GetColorOfVertex(int iIndex);
	float		GetHeightOfVertex(int iIndex);

	virtual HRESULT CreateVertexData() override;
	virtual	HRESULT CreateIndexData() override;
	
public:
	xMap();
	virtual ~xMap();
};

