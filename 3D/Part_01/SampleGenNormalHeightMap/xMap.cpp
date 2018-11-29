#include "xMap.h"
bool    xMap::CreateHeightMap(ID3D11Device* pDevice,
	ID3D11DeviceContext*	pContext,
	T_STR szName)
{
	HRESULT hr;
	D3DX11_IMAGE_INFO imageinfo;
	ID3D11Resource* pLoadTexture = nullptr;
	D3DX11_IMAGE_LOAD_INFO info;	
	ZeroMemory(&info, sizeof(info));
	info.MipLevels = 1;
	info.Usage = D3D11_USAGE_STAGING;
	info.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	info.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	info.pSrcInfo = &imageinfo;

	if (FAILED(hr = D3DX11CreateTextureFromFile(pDevice,
		szName.c_str(), &info, NULL, &pLoadTexture, NULL)))
	{
		return false;
	}

	ID3D11Texture2D* pTex2D = nullptr;
	if( FAILED(pLoadTexture->QueryInterface(
				__uuidof(ID3D11Texture2D),
				(LPVOID*)&pTex2D)))
	{
		return false;
	}
	SAFE_RELEASE(pLoadTexture);

	D3D11_TEXTURE2D_DESC desc;
	pTex2D->GetDesc(&desc);
	
	m_fHeightList.resize(desc.Height*desc.Width);

	D3D11_MAPPED_SUBRESOURCE map;
	UINT index = D3D11CalcSubresource(0, 0, 1);
	if (SUCCEEDED(pContext->Map(pTex2D, 
		index, D3D11_MAP_READ, 0, &map)))
	{
		UCHAR* pTexels = (UCHAR*)map.pData;
		for (UINT iRow = 0; iRow < desc.Height; iRow++)
		{
			UINT rowStart = iRow * map.RowPitch;
			for (UINT iCol= 0; iCol < desc.Width; iCol++)
			{
				UINT colStart = iCol * 4;
				UCHAR uRed = pTexels[rowStart + colStart +0];
				m_fHeightList[iRow*desc.Width+ iCol] = uRed;
			}
		}
		pContext->Unmap(pTex2D, index);
	}
	m_iNumRows = desc.Height;
	m_iNumCols = desc.Width;
	return true;
}
HRESULT xMap::CreateVertexData()
{
	m_iNumVertex = m_iNumVertices;
	m_VertexList.resize(m_iNumVertices);
	float fHalfCols = (m_iNumCols-1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;
	float fOffsetU = 1.0f / (m_iNumCols - 1);
	float fOffsetV = 1.0f / (m_iNumRows - 1);

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iIndex = iRow * m_iNumCols + iCol;
			m_VertexList[iIndex].p.x = (iCol-fHalfCols)*m_fCellDistance;
			m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex);
			m_VertexList[iIndex].p.z = -((iRow - fHalfRows)*m_fCellDistance);
			m_VertexList[iIndex].n = GetNormalOfVertex(iIndex);
			m_VertexList[iIndex].c = GetColorOfVertex(iIndex);
			m_VertexList[iIndex].t = GetTextureOfVertex(fOffsetU*iCol, fOffsetV*iRow);
		}
	}
	return S_OK;
}

HRESULT xMap::CreateIndexData()
{
	m_iNumIndex = m_iNumFace * 3;
	m_IndexList.resize(m_iNumIndex);
	int iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{		
			// 0  1   2
			// 3  4   5
			int iNextRow = iRow + 1;
			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0]+1;
			m_IndexList[iIndex + 2] = iNextRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2]+1;
			iIndex += 6;
		}
	}

	GenVertexNormal();
	return S_OK;
}
bool xMap::GenVertexNormal()
{
	InitFaceNormals();
	GenNormalLookupTable();
	CalcPerVertexNormalsFastLookup();
	return true;
}
void xMap::InitFaceNormals()
{
	m_FaceNormalList.resize(m_iNumFace);
}
void xMap::CalcFaceNormals()
{
	int iFaceIndex = 0;
	for (int iIndex = 0; iIndex < m_IndexList.size(); iIndex += 3)
	{
		DWORD i0 = m_IndexList[iIndex];
		DWORD i1 = m_IndexList[iIndex + 1];
		DWORD i2 = m_IndexList[iIndex + 2];
		m_FaceNormalList[iFaceIndex++] = ComputeFaceNormal(i0, i1, i2);
	}
}
D3DXVECTOR3 xMap::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
{
	D3DXVECTOR3 vNormal;
	D3DXVECTOR3 v0 = m_VertexList[i1].p - m_VertexList[i0].p;
	D3DXVECTOR3 v1 = m_VertexList[i2].p - m_VertexList[i0].p;
	D3DXVec3Cross(&vNormal, &v0, &v1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	return vNormal;
}
void xMap::GenNormalLookupTable()
{	
	m_NormalLooupTabel.resize(m_iNumVertex);
	for (int iFace = 0; iFace < m_iNumFace; iFace++)
	{
		for (int iVertex = 0; iVertex < 3; iVertex++)
		{
			for (int iTable = 0; iTable < 6; iTable++)
			{
				int iIndex = m_IndexList[iFace*3+iVertex];
				if (m_NormalLooupTabel[iIndex].faceIndex[iTable] == -1)
				{
					m_NormalLooupTabel[iIndex].faceIndex[iTable] =
						iFace;
					break;
				}
			}
		}
	}
}
void xMap::CalcPerVertexNormalsFastLookup()
{
	CalcFaceNormals();
	for (int iVertex = 0; iVertex < m_NormalLooupTabel.size(); iVertex++)
	{
		D3DXVECTOR3 avgNormal(0,0,0);
		int iFace = 0;
		for (iFace = 0; iFace < 6; iFace++)
		{
			if (m_NormalLooupTabel[iVertex].faceIndex[iFace] != -1)
			{
				int iFaceIndex = m_NormalLooupTabel[iVertex].faceIndex[iFace];
				avgNormal += m_FaceNormalList[iFaceIndex];
			}
			else
			{
				break;
			}
		}
		D3DXVec3Normalize(&m_VertexList[iVertex].n, &avgNormal);
		// 조명계산
		D3DXVECTOR3 vLight(100, 100, 100);
		D3DXVec3Normalize(&vLight, &vLight);
		float fDot = D3DXVec3Dot(&m_VertexList[iVertex].n,&vLight);
		m_VertexList[iVertex].c.x = fDot;
		m_VertexList[iVertex].c.y = fDot;
		m_VertexList[iVertex].c.z = fDot;
	}
}
D3DXVECTOR2 xMap::GetTextureOfVertex(float fU, float fV)
{
	return D3DXVECTOR2(fU*50, fV*50);
}

D3DXVECTOR3 xMap::GetNormalOfVertex(int iIndex)
{
	return D3DXVECTOR3(0.0f, 1.0f, 0.0f );
}

D3DXVECTOR4 xMap::GetColorOfVertex(int iIndex)
{
	return D3DXVECTOR4(
		randstep(0.0f, 1.0f), 
		randstep(0.0f, 1.0f),
		randstep(0.0f, 1.0f), 1.0f );
}

float xMap::GetHeightOfVertex(int iIndex)
{
	if (m_fHeightList.size() > 0)
	{
		return m_fHeightList[iIndex] * m_fScaleHeight;
	}
	return 0.0f;
}

bool	xMap::CreateMap(xMapDesc desc)
{	
	m_iNumRows = desc.iNumRows;
	m_iNumCols = desc.iNumCols;
	m_iNumCellRows = m_iNumRows-1;
	m_iNumCellCols= m_iNumCols-1;
	m_iNumVertices = m_iNumRows * m_iNumCols;
	m_iNumFace = m_iNumCellRows* m_iNumCellCols*2;
	m_fCellDistance = desc.fDistance;
	m_fScaleHeight = desc.fScaleHeight;
	return true;
}

bool    xMap::Load(ID3D11Device* pDevice, xMapDesc desc)
{
	m_pd3dDevice = pDevice;
	if (!CreateMap(desc))
	{
		return false;
	}
	xShape::Create(m_pd3dDevice,desc.szShaderFile,desc.szTextureFile);
	return true;
}
bool	xMap::Init()
{	
	return true;
}
bool	xMap::Frame()
{
	return xShape::Frame();
}
bool	xMap::Render(ID3D11DeviceContext* pContext)
{
	xShape::Render(pContext);
	return true;
}
bool	xMap::Release()
{
	xShape::Release();
	return true;
}

xMap::xMap()
{
	m_fScaleHeight = 1;
}


xMap::~xMap()
{
}
