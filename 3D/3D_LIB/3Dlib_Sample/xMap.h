#pragma once
#include "xShape.h"
struct xMapDesc
{
	int   iNumCols;
	int   iNumRows;
	float  fDistance;
	float  fScaleHeight;
	T_STR  szTextureFile;
	T_STR  szShaderFile;
};
struct TIndexTable
{
	int faceIndex[6];
	TIndexTable() {
		faceIndex[0] = -1;
		faceIndex[1] = -1;
		faceIndex[2] = -1;
		faceIndex[3] = -1;
		faceIndex[4] = -1;
		faceIndex[5] = -1;
	}
};
class xMap : public xShape
{
public:
	xMapDesc   m_xMapDesc;
	int		m_iNumRows;
	int		m_iNumCols;
	int		m_iNumCellRows;
	int		m_iNumCellCols;
	int	    m_iNumFace;
	int     m_iNumVertices;
	float   m_fCellDistance;
	float   m_fScaleHeight;
	vector<float> m_fHeightList;
	vector<D3DXVECTOR3> m_FaceNormalList;
	vector<TIndexTable> m_NormalLooupTabel;
public:
	float  Lerp(float fStart, float fEnd, float fTangent);
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	D3DXVECTOR2 GetTextureOfVertex(float fU, float fV);
	D3DXVECTOR3 GetNormalOfVertex(int iIndex);
	D3DXVECTOR4 GetColorOfVertex(int iIndex);
	float       GetHeightOfVertex(int iIndex);
	// 기하쉐이더(기본값은 구를 생성) 생략함.
	HRESULT LoadGeometryShader(T_STR  szName) {
		return S_OK;
	};
	bool	GenVertexNormal();
	bool    CreateHeightMap(
		ID3D11Device* pDevice, 
		ID3D11DeviceContext*	pContext,
		T_STR szName);
	bool	CreateMap(xMapDesc desc);
	bool    Load(ID3D11Device* pDevice,xMapDesc desc);
	bool	Init();
	bool	Frame();
	bool	Render(ID3D11DeviceContext* pContext);
	bool	Release();
public:
	float  GetHeightmap(int row, int col);
	float  GetHeight(float fPosX, float fPosY);
	void InitFaceNormals();
	void CalcFaceNormals();
	void GenNormalLookupTable();
	void CalcPerVertexNormalsFastLookup();
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);
public:
	xMap();
	virtual ~xMap();
};

