#include "xShape.h"
HRESULT xSphereShape::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_iVertexSize = sizeof(_PNCT_VERTEX);
	DX::CreateVertexBuffer(m_pd3dDevice,
		m_iNumVertex,
		sizeof(_PNCT_VERTEX),
		&m_vList.at(0),
		m_dxObj.m_pVertexBuffer.GetAddressOf());
	return hr;
}
// 로칼 정점의 크기를 정규화하여 1로 만든다.
_PNCT_VERTEX xSphereShape::NormalizeVertex(
	_PNCT_VERTEX Vertex)
{
	_PNCT_VERTEX newvertex;// = (PNCT_VERTEX)0;
	D3DXVec3Normalize(&newvertex.p, &Vertex.p);
	// 정점이 원점을 중심으로 하는 노말 벡터가 된다.
	newvertex.n = newvertex.p;
	newvertex.c = Vertex.c;
	newvertex.t = Vertex.t;
	return newvertex;
}
void xSphereShape::TriAppend(
	_PNCT_VERTEX V0, _PNCT_VERTEX V1, _PNCT_VERTEX V2,
	vector<_PNCT_VERTEX>& TriStream, int iIndex)
{
	TriStream[iIndex + 0] = NormalizeVertex(V0);
	TriStream[iIndex + 1] = NormalizeVertex(V1);
	TriStream[iIndex + 2] = NormalizeVertex(V2);
}

HRESULT xSphereShape::CreateVertexData() 
{
	xBoxShape::CreateVertexData();	
	xBoxShape::CreateIndexData();
	vector<_PNCT_VERTEX>  vList;
	vList.resize(m_IndexList.size());
	m_vList.resize((m_IndexList.size() / 3) * 12);
	for (int iFace = 0; iFace < 12; iFace++)
	{
		int iCount = iFace * 3;
		vList[iCount+  0] = m_VertexList[m_IndexList[iCount + 0]];
		vList[iCount + 1] = m_VertexList[m_IndexList[iCount + 1]];
		vList[iCount + 2] = m_VertexList[m_IndexList[iCount + 2]];
	}
	int iIndex = 0;
	for (int iFace = 0; iFace < 12; iFace++)
	{
		_PNCT_VERTEX input[3];
		input[0] = vList[iFace * 3 + 0];
		input[1] = vList[iFace * 3 + 1];
		input[2] = vList[iFace * 3 + 2];

		_PNCT_VERTEX Center0, Center1, Center2;
		Center0.p = D3DXVECTOR3((input[0].p + input[1].p) / 2.0);
		Center0.n = (input[0].n + input[1].n) / 2.0;
		Center0.c = (input[0].c + input[1].c) / 2.0;
		Center0.t = (input[0].t + input[1].t) / 2.0;

		Center1.p = D3DXVECTOR3((input[1].p + input[2].p) / 2.0);
		Center1.n = (input[1].n + input[2].n) / 2.0;
		Center1.c = (input[1].c + input[2].c) / 2.0;
		Center1.t = (input[1].t + input[2].t) / 2.0;

		Center2.p = D3DXVECTOR3((input[0].p + input[2].p) / 2.0);
		Center2.n = (input[0].n + input[2].n) / 2.0;
		Center2.c = (input[0].c + input[2].c) / 2.0;
		Center2.t = (input[0].t + input[2].t) / 2.0;

		
		TriAppend(input[0], Center0, Center2,
			m_vList, iIndex);
		iIndex += 3;
		TriAppend(Center0, input[1], Center1, 
			m_vList, iIndex);
		iIndex += 3;
		TriAppend(input[2], Center2, Center1, 
			m_vList, iIndex);
		iIndex += 3;
		TriAppend(Center0, Center1, Center2,
			m_vList, iIndex);
		iIndex += 3;
	}

	m_iNumVertex = m_vList.size();
	m_iNumIndex = m_vList.size();
	return S_OK;
};
HRESULT xSphereShape::LoadVertexShader(T_STR  szName) {
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexShader.Attach(
		DX::LoadVertexShaderFile(m_pd3dDevice,
			szName.c_str(),
			m_dxObj.m_pVSBlob.GetAddressOf(), "VS_NoMatrix"));
	return hr;
}
HRESULT xSphereShape::LoadGeometryShader(T_STR  szName)
{
	return xShape::LoadGeometryShader(szName);
}
xSphereShape::xSphereShape()
{

}

xSphereShape::~xSphereShape()
{

}