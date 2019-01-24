#pragma once
#include "S_Object.h"
#define MAX_WEIGHT_BIPED 8

struct SBipedVertex
{
	int m_dwNumWeight;
	vector<BYTE> m_BipIDList;
	vector<float> m_fWeightList;
};

struct P3NCT3VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float w[4];
	float i[4];
};

struct PNCT5_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float w1[4];
	float i1[4];
	float w2[4];
	float i2[4];
};
struct SSkinTri :public STri
{
	PNCT5_VERTEX m_vVertex[3];
};
struct SSkinMesh : public SMesh
{
	vector<SSkinTri> m_SkinTriList;
	vector<SSkinMesh*> m_pSkinSubMesh;

	int m_iNumTex;
	int m_iTexType[13];
	TCHAR m_szTexName[13][30];
	SSkinMesh() {};
	virtual ~SSkinMesh() {};
};

class S_Skin : public SSingleton<S_Skin>
{
private:
	friend class SSingleton<S_Skin>;
public:
	SScene m_Scene;
	typedef vector<SBipedVertex> SBIPED_VERTEX_VECTOR;
	SBIPED_VERTEX_VECTOR m_BipedList;

	typedef vector<SSkinMesh*> SSKINMESH_VECTOR;
	SSKINMESH_VECTOR m_SkinmeshList;
public:
	bool		Init();
	bool		skmExport();
	bool		Release();
	Modifier*	FindModifier(INode *nodePtr, Class_ID classID);
	void		SetBipedInfo(INode* node);
	void		ExportPhysiqueData(INode* node, Modifier	*phyMod);
	void		ExportSkinData(INode* node, Modifier	*skinMod);
	bool		ExportMesh(FILE* fp, SSkinMesh* pMesh);
	void		SetVertexBiped(INode* node, Face*	face,
		int v0, int v1, int v2,
		SSkinTri* pTri);
	bool		GetNodeInfo(INode* node, TimeValue t);
	
	void		GenerateGroup(INode* node, Mesh *mesh, SSkinMesh* pSkinMesh);
	void		LoadMaterial(SSkinMesh*	pSkinMesh, Mtl* mtl);
	void		SetTriangle(INode* node, Mesh *mesh, SSkinMesh* pSkinMesh, SSkinMesh*	pSumMesh = NULL, int iMtrl = 0);
	int			GetMapID(Class_ID cid, int subNo);
	int			IsEqulVertexList(vector<PNCT5_VERTEX>&  VertexArray, PNCT5_VERTEX& Vertex);
public:
public:
	S_Skin();
	virtual ~S_Skin();
};
#define I_SkinExp S_Skin::GetInstance()
