#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ID_ASE_AM 0  // ambient
#define ID_ASE_DI 1  // diffuse
#define ID_ASE_SP 2  // specular
#define ID_ASE_SH 3  // shininesNs
#define ID_ASE_SS 4  // shininess stregth
#define ID_ASE_SI 5  // self-illumination
#define ID_ASE_OP 6  // opacity
#define ID_ASE_FI 7  // filter color
#define ID_ASE_BU 8  // bump
#define ID_ASE_RL 9  // reflection
#define ID_ASE_RR 10 // refraction
#define ID_ASE_DP 11 // displacement
#define ID_ASE_GN 12 // Generic
#define ID_ASE_EV 13 // EnvMap

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
struct xMtrlerial
{
	vector<xTextureMap> m_mapList;
	vector<xMtrlerial>	m_SubMaterial;
};
struct xIndex
{
	int i[3];
	int iSubMtrl;
};
struct xGeomMesh
{
	int mtrlRef;
	T_STR name;
	D3DXMATRIX matWorld;
	vector<D3DXVECTOR3> vertexList;
	vector<xIndex> PosFaceList;

	vector<D3DXVECTOR3> texList;
	vector<xIndex> texFaceList;

	vector<D3DXVECTOR3> ColList;
	vector<xIndex> ColFaceList;

	vector<D3DXVECTOR3> NorList;
};
class x_AseMesh
{
public:
	xScene m_Scene;
	FILE*	m_pStream;
	int m_iTemp;
	TCHAR m_pBuffer[256];
	TCHAR m_pString[256];
	TCHAR m_pString2[256];
	xMtrlerial xMtrl;
	xTextureMap tMap;
	vector<xMtrlerial>	m_MaterialList;
	vector<xGeomMesh>	m_ObjectList;
public:
	bool	Load(T_STR name);
	void	LoadScene();
	void	LoadMaterial();
	void	LoadGeomObject();
	void	GetData(void* pData);
	bool	FineString(T_STR find);
	void	LoadVertexData(D3DXVECTOR3& v, bool bSwap = true);
	void	LoadIndexData(xIndex& v);
public:
	x_AseMesh();
	virtual ~x_AseMesh();
};

