#pragma once
#include "Header.h"
typedef struct _D3DMATRIX_ {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} _D3DMATRIX;
struct SScene
{
	int iFirstFrame;
	int iLastFrame;
	int iFrameSpeed;
	int iTickPerFrame;
	int iNumObject;
	int iNumMtrl;
};
struct xTextureMap
{
	int iType;
	TSTR name;
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
	TSTR name;
	_D3DMATRIX matWorld; // MAX = Matrix3 4x3
	vector<Point3> vertexList;
	vector<xIndex> PosFaceList;

	vector<Point2> texList;
	vector<xIndex> texFaceList;

	vector<Point4> ColList;
	vector<xIndex> ColFaceList;

	vector<Point3> NorList;
};
class S_KHJGlobal
{
public:
	Interface * m_pMax;
	TSTR		m_szFileName;
//	TSTR NAME; //TSTR max에서 사용하는거
	INode*		m_pRootNode;
	Interval    m_Interval;
	SScene		m_Scene;
	vector<INode*>		m_ObjectList;
	vector<Mtl*>		m_MtrlList;
	vector<xMtrlerial>		m_xMtrlList;
	vector<xGeomMesh>		m_xObjectList;
	
public:
	void PreProcess(INode* pNode);
	void Initialize(Interface *i, TSTR name);
	void AddObject(INode* pNode);
	void AddMtl(INode* pNode);
public:
	S_KHJGlobal();
	virtual ~S_KHJGlobal();
};

