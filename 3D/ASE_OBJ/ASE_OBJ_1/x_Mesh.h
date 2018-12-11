#pragma once
#include "xShape.h"
class x_Mesh: public xShape
{
public:
	vector<x_Mesh> m_ObjectList;
	vector<PNCT_VERTEX>  m_TempVertexList;
	int m_iNumFaces;
public:
	virtual HRESULT LoadGeometryShader(T_STR  szName)
	{
		return S_OK;
	}
	/*virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;*/
public:
	x_Mesh();
	virtual ~x_Mesh();
};

