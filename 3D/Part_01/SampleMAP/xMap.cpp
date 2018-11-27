#include "xMap.h"


bool xMap::CreateMap(xMapDesc desc)
{
	// 2n+1,
	// 2n+1,1+1,2,4,8,16,
	
	/*if (desc.iNumCols > 1025)
		desc.iNumCols = 1205;*/
	
	m_iNumRows = desc.iNumRows;
	m_iNumCols=desc.iNumCols;
	m_iNumCellRows=m_iNumRows-1;
	m_iNumCellCols = m_iNumCols - 1;;
	m_iNumVertices=m_iNumRows*m_iNumCols;
	m_iNumFace = m_iNumCellRows * m_iNumCellCols*2;
	m_fColliDistance=desc.fDistance;
	return true;
}

bool xMap::Load(ID3D11Device* pDevice,xMapDesc desc)
{
	m_pd3dDevice = pDevice;
	if (!CreateMap(desc))
	{
		return false;
	}
	xBoxShape::Create(m_pd3dDevice,
		desc.szShaderFile,
		desc.szTextureFile);
	return true;
}
bool xMap::Init()
{
	return true;
}
bool xMap::Frame()
{
	return true;
}
bool xMap::Release()
{
	return true;
}
bool xMap::Render(ID3D11DeviceContext* pContext)
{
	xBoxShape::Render(pContext);
	return true;
}

D3DXVECTOR2 xMap::GetTextureOfVertex(float fU,float fV)
{
	return D3DXVECTOR2(fU,fV);
}

D3DXVECTOR3 xMap::GetNormalOfVertex(int iIndex)
{
	return D3DXVECTOR3();
}

D3DXVECTOR4 xMap::GetColorOfVertex(int iIndex)
{
	return D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

float xMap::GetHeightOfVertex(int iIndex)
{
	return 0.0f;
}

HRESULT xMap::CreateVertexData()
{
	m_iNumVertex = m_iNumVertices;
	m_VertexList.resize(m_iNumVertices);
	float fHalfCols = (m_iNumCols - 1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;

	float fOffsetU = 1.0f / (m_iNumCols - 1);
	float fOffsetV = 1.0f / (m_iNumRows - 1);
	
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iIndex = iRow * m_iNumCols + iCol;
			m_VertexList[iIndex].p.x = (iCol-fHalfCols)*m_fColliDistance;
			m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex);
			m_VertexList[iIndex].p.z = -((iRow - fHalfRows)*m_fColliDistance);
			m_VertexList[iIndex].n = GetNormalOfVertex(iIndex);
			m_VertexList[iIndex].c = GetColorOfVertex(iIndex);
			m_VertexList[iIndex].t = GetTextureOfVertex(fOffsetU*iCol,fOffsetV*iRow);
		}
	}
	return S_OK;
}

HRESULT xMap::CreateIndexData()
{
	m_iNumIndex = m_iNumFace * 3;
	m_IndexList.resize(m_iNumIndex *3);
	int iIndex = 0;

	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			// 0 1 2
			// 3 4 5
			int iNextRow = iRow + 1;
			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] + 1;
			m_IndexList[iIndex + 2] = iNextRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2] + 1;
			iIndex += 6;
		}
	}
	return S_OK;
}



xMap::xMap()
{
}


xMap::~xMap()
{
}
