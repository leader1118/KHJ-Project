#pragma once
#include "KHJ_Object.h"
// include ->C:\Program Files(x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\atlmfc\include
// lib -> C:\Program Files(x86)\Windows Kits\10\Lib\10.0.15063.0\ucrt\x64

#define MAX_WEIGHT_BIPED 8

// 정점당 1개 씩 할당 필요

struct SBipedVertex
{
	int m_dwNumWeight;
	vector<BYTE> m_BipIDList;
	vector<float> m_fWeightList;
};

// 쉐이더 사용시 ( 가중치 4개 제한 사용)
struct P3NCT3_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float w[4]; // w0, fw1, fw2, fNumWeight;
	float i[4]; // i0, i1, i2, i3
};

// 쉐이더 사용시 (가중치 8개 제한 사용)
struct PNCT5_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float w1[4]; // w0, fw1, fw2, fw3
	float i1[4]; // i0, i1, i2, i3
	float w2[4]; // w4, fw5, fw6, fNumWeight;
	float i2[4]; // i4, i5 ,i6 ,i7
};
struct SSkinTri : public STri
{
	PNCT5_VERTEX m_vVertex[3];
};
struct SSkinMesh :public SMesh
{
	vector<SSkinTri> m_SkinTriList;
	vector<SSkinMesh*> m_pSkinSubMesh;
	// 텍스쳐 정보 (텍스쳐 맵 단위)
	int m_iNumTex;
	int m_iTexType[13];
	TCHAR m_szTexName[13][30];
	SSkinMesh() {};
	virtual ~SSkinMesh() {};
};

class KHJ_SkinExp : public TSingleton<KHJ_SkinExp>
{
private:
	friend class TSingleton<KHJ_SkinExp>;
public:
	SScene		m_Scene;
	// 정점 가중치 리스트
	typedef vector<SBipedVertex> TBIPED_VERTEX_VECTOR;
	TBIPED_VERTEX_VECTOR m_BipedList;
	// 메쉬 페이스 리스트
	typedef vector<SSkinMesh*> SSKINMESH_VECTOR;
	SSKINMESH_VECTOR	 m_SkinMeshList;
public:
	bool Init();
	bool skmExport();
	bool Release();
	Modifier* FindModifier(INode* nodePtr, Class_ID classID);
	void SetBipedInfo(INode* node);
	void ExportPhysiqueData(INode* node, Modifier *phyMod);
	void ExportSkinData(INode* node, Modifier * skinMod);
	bool ExportMesh(FILE* fp, SSkinMesh* pMesh);
	void SetVertexBiped(INode* node, Face* face, int v0, int v1, int v2, SSkinTri* pTri);
	bool GetNodeInfo(INode* node, TimeValue t);

	// 서브메터리얼 사용시를 고려하여 페이스 리스트 생성
	void GenerateGroup(INode* node, Mesh* mesh, SSkinMesh* pSkinMesh);
	void LoadMaterial(SSkinMesh* pSkinMesh, Mtl* mtl);
	void SetTriangle(INode* node, Mesh* mesh, SSkinMesh* pSkinMesh, SSkinMesh* pSumMesh = NULL, int iMtrl = 0);
	int GetMapID(Class_ID cid, int subNo);
	int IsEqulVertexList(vector<PNCT5_VERTEX>& VertexArray, PNCT5_VERTEX& Vertex);
public:
	KHJ_SkinExp(void);
	virtual ~KHJ_SkinExp(void);
};
#define I_SkinExp KHJ_SkinExp::GetInstance()

