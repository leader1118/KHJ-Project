#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "xStd.h"


struct xScene
{
	int iFirstFrame;
	int iLastFrame;
	int iFrameSpeed;
	int iTickPerFrame;
};
struct xTextureMap
{
	int iType;
	T_STR name;
};
struct xMaterial
{
	vector<xTextureMap> m_mapList;
	vector<xMaterial> m_SubMaterial;
};
struct xIndex
{
	int i[3];
	int iSubMtrl;
};
struct xGeomMesh
{
	int mtraRef;
	T_STR name;
	D3DXMATRIX matWorld;
	vector<D3DXVECTOR3> vertexList;
	vector<xIndex> PosFaceList;

	vector<D3DXVECTOR2> texList;
	vector<xIndex> texFaceList;

	vector<D3DXVECTOR4> ColList;
	vector<xIndex> ColFaceList;

	vector<D3DXVECTOR3> NorfaceList;
};
class x_AseMesh
{
public:
	xScene m_Scene;
	FILE* pStream;
	TCHAR m_pBuffer[256];
	TCHAR m_pString[256];
	TCHAR m_pString2[256];
	xMaterial xMat;
	xTextureMap tMap;
	vector<xMaterial>	m_MaterialList;
	vector<xGeomMesh>	m_ObjectList;
public:
	bool Load(T_STR name);
	void LoadScene();
	void LoadMaterial();
	void LoadGeomObject();
	void GetData(void* pData);
public:
	x_AseMesh();
	virtual ~x_AseMesh();
};

