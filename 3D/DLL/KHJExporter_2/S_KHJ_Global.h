#pragma once
#include "Header.h"
#include "TemplateMap.h"

#define CTL_CHARS 31
#define SINGLE_QUOTE 39
#define ALMOST_ZERO 1.0e-3f

typedef struct _D3D_MATRIX
{
	union {
		struct {
			float	_11, _12, _13, _14;
			float	_21, _22, _23, _24;
			float	_31, _32, _33, _34;
			float	_41, _42, _43, _44;
		};
		float m[4][4];
	};
}D3D_MATRIX, *LPD3D_MATRIX;

typedef class Matrix3	*LPMATRIX3;


struct P3NCVERTEX
{
	float Px, Py, Pz;
	float Nx, Ny, Nz;
	Point4 c;
};
struct PNCT_VERTEX
{
	Point3	p;
	Point3	n;
	Point4	c;
	Point2	t;
};

const enum OBJECTCLASSTYPE
{
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};

struct STri
{
	PNCT_VERTEX v[3];
	int iSubIndex;
};

struct SScene
{
	int iVersion; // ���� ����
	int iFirstFrame; // ���� ������
	int iLastFrame; // ������ ������
	int iFrameSpeed; // 1�ʴ� ������ ����(30)
	int iTickPerFrame; // 1�������� ƽ ��(160)
	int iNumMesh; // �޽� ������Ʈ ����
	int iMaxweight; // ���� �� ����ġ
	int iBindPose; // ���ε� ���� �ִϸ��̼� ����
};

struct STexMap
{
	int iIndex;
	int iType; // �ؽ��� Ÿ�� �ε���
	TSTR StrTextureName; // �ؽ��� �̸�
};

struct SMtl
{
	int iIndex;
	int iNumSubMtl; // ���� ���͸��� ����
	int iNumMap; // �ؽ��� �� ����
	TSTR strName; // ���͸��� �̸�
	TSTR strClassName; // ��Ŭ���� �̸�
	vector<STexMap> TexMaps; // �� Ÿ��Ʋ
	vector<SMtl> SubMaterial; // ���� ���͸��� ���� ����
};
struct SAnimTrack
{
	int iType;
	int iTick;
	Quat qValue;
	Point3 vValue;
};

struct SMESH_HEADER
{
	OBJECTCLASSTYPE m_ClassType;
	Box3			m_Box;
	D3D_MATRIX		m_matWorld;
	int				m_iNumVertex;
	int				m_iNumFace;
	int				m_iMtrlRef;
	int				m_iNumTrack[4];
};

struct SMesh : public SMESH_HEADER
{
	TSTR			m_strNodeName;
	TSTR			m_strParentName;
	vector<SAnimTrack> m_PosTrack;
	vector<SAnimTrack> m_RotTrack;
	vector<SAnimTrack> m_SclTrack;
	vector<SAnimTrack> m_VisTrack;

	vector<STri>		m_TriList;
	vector<SMesh*>		m_pSubMesh;

	SMesh()
	{
		m_iMtrlRef = -1;
		m_iNumFace = 0;
		m_iNumTrack[0] = 0;
		m_iNumTrack[1] = 0;
		m_iNumTrack[2] = 0;
		m_iNumTrack[3] = 0;
		m_ClassType = CLASS_GEOM;
	};
	~SMesh()
	{
		m_PosTrack.clear();
		m_RotTrack.clear();
		m_SclTrack.clear();
		m_VisTrack.clear();
		m_TriList.clear();
	};
};

struct MATRIXINDEX
{
	OBJECTCLASSTYPE			m_ClassType;
	int						m_iIndex; // �ִϸ��̼� ����� �ε���
	T_STR					m_szName; // �ִϸ��̼� ����� �̸�
	vector<P3NCVERTEX>		m_VertexList; // �޽� ���̽� ����Ʈ
	Matrix3					m_NodeTM;
	Matrix3					m_InvNodeTM;
	INode*					m_pINode;
	Object*					m_pObj;
	Control*				m_pControl;
	SMesh					m_sMesh;

	void Add(int iIndex, T_STR szName)
	{
		m_pObj = NULL;
		m_pControl = NULL;
		m_iIndex = iIndex;
		m_szName = szName;
	}

	void SetNode(INode* pNode, int iTick, MATRIXINDEX* pParentIndex = 0)
	{
		m_pINode = pNode;
		m_pObj = m_pINode->GetObjectRef();
		m_pControl =m_pINode->GetTMController();
			
		m_ClassType = CLASS_GEOM;

		if (m_pObj && m_pObj->ClassID() == Class_ID(BONE_CLASS_ID, 0)) // �� ������Ʈ
		{
			m_ClassType = CLASS_BONE;
		}
		if (m_pObj && m_pObj->ClassID() == Class_ID(DUMMY_CLASS_ID,0)) // ���� ������Ʈ
		{
			m_ClassType = CLASS_DUMMY;
		}
		if (m_pControl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID || // ��Ʈ �����е� ������ ��� �����е��
			m_pControl->ClassID() == BIPBODY_CONTROL_CLASS_ID) // ��Ʈ �����е� 1��
		{
			m_ClassType = CLASS_BIPED;
		}

		m_NodeTM = pNode->GetNodeTM(iTick);
		m_InvNodeTM = Inverse(m_NodeTM);

	}

	void Release()
	{
		for (int iSub = 0; iSub < m_sMesh.m_pSubMesh.size(); iSub++)
		{
			SAFE_DEL(m_sMesh.m_pSubMesh[iSub]);
		}
		m_sMesh.m_pSubMesh.clear();
	};
};

class S_KHJ_Global
{
public:
	Interface*	m_p3dsMax; // �ƽ� �������̽�
	INode*		m_pRootNode;
	Interval	m_Interval; // ������ ����
	SScene		m_Scene; // �� ���� ����
	TTemplateMap<MATRIXINDEX> m_MatrixMap;
	vector<Mtl*> m_pMtlList; // ���͸��� ����Ʈ
	vector<SMtl> m_Material; // ��� �� ���� ����Ʈ
	TSTR		 m_CurtFileName; // �ƽ� ���� �̸�
	TCHAR		 m_tmpBuffer[MAX_PATH]; // �ӽ� ����
public:
	bool CheckFile(Interface* pMax);
	bool Initialize(Interface* p3dsMax = NULL,TSTR name);
	void PreProcess(INode* pNode);
	void AddObject(INode* pNode);
	void AddMtl(INode* pNode); // �ߺ����� �ʰ� ���͸��� �߰�
	int  GetMtlref(Mtl* pMtl); // pMtl�� ����� �ε����� ��ȯ�Ѵ�.
	void SetBindPose(bool bBindPose = false) { m_Scene.iBindPose = bBindPose; }
	int  GetIndex(const TCHAR* strNodeName);
public:
	void DumpMatrix3(Matrix3* m, D3D_MATRIX& mat);
	void DumpPoint3(Point3& pDest, Point3& pSrc);
	bool TMNegParity(Matrix3 &m);
	bool EqualPoint2(Point2 p1, Point2 p2);
	bool EqualPoint3(Point3 p1, Point3 p2);
	bool EqualPoint4(Point4 p1, Point4 p2);
	TCHAR* FixupName(MSTR Name);
public:
	S_KHJ_Global(void);
	virtual ~S_KHJ_Global(void);
};

