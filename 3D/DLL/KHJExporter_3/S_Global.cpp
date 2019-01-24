#include "S_Global.h"

int S_Global::GetIndex(const TCHAR* strNodeName)
{
	return m_MatrixMap.GetID(strNodeName);
}
bool S_Global::CheckFile(Interface* pMax)
{
	TSTR curtFileName = FixupName(pMax->GetCurFileName());
	if (curtFileName.isNull() == false && m_CurtFileName == curtFileName)
	{
		return false;
	}
	m_MatrixMap.Release();
	m_pMtlList.clear();

	m_CurtFileName = curtFileName;
	return true;
}

bool S_Global::Initialize(Interface* pMax)
{
	m_p3dsMax = pMax;
	m_pRootNode = pMax->GetRootNode();

	if (pMax == NULL && m_pRootNode == NULL)
	{
		return false;
	}

	if (CheckFile(pMax) == false)return true;

	// scene 정보 얻기
	m_Interval = m_p3dsMax->GetAnimRange();

	memset(&m_Scene, 0, sizeof(m_Scene));

	m_Scene.iVersion = 20190121;
	m_Scene.iFirstFrame = m_Interval.Start() / GetTicksPerFrame();
	m_Scene.iLastFrame = m_Interval.End() / GetTicksPerFrame();
	m_Scene.iFrameSpeed = GetFrameRate();
	m_Scene.iTickPerFrame = GetTicksPerFrame();

	// 최 상위 INode 얻기
	PreProcess(m_p3dsMax->GetRootNode());

	m_Scene.iNumMesh = m_MatrixMap.Count();
	m_Scene.iMaxWeight = 1;
	return true;
}

void S_Global::PreProcess(INode* pNode)
{
	if (pNode == NULL)return;

	AddObject(pNode);
	AddMtl(pNode);
	
	//  재귀 호출
	int iNumChildren = pNode->NumberOfChildren(); // pNode의 자식 노드 개수를 반환함.
	for (int iCnt = 0; iCnt < iNumChildren; iCnt++)
	{
		INode* pChild = pNode->GetChildNode(iCnt); // iCnt 번째의 자식 노드를 반환함.
		PreProcess(pChild);
	}
}

void S_Global::AddObject(INode* pNode)
{
	// 오브젝트 추가
	ObjectState os = pNode->EvalWorldState(m_Interval.Start());
	// 타켓 클래스인 오브젝트는 불필요한 오브젝트이다.
	if (os.obj)
	{
		// 타켓 클래스인 오브젝트는 불필요한 오브젝트이다.
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
		{
			return;
		}
		switch (os.obj->SuperClassID())
		{
		case GEOMOBJECT_CLASS_ID:
		case HELPER_CLASS_ID:
		{
			int iIndex = m_MatrixMap.Add(pNode->GetName());
			TSTR parentname = pNode->GetParentNode()->GetName();
			m_MatrixMap.GetPtr(iIndex)->SetNode(pNode, m_Interval.Start(), m_MatrixMap.GetPtr(parentname));

		}
		break;
		}
	}
}

void S_Global::AddMtl(INode* pNode)
{
	// 매터리얼 추가(중복 제거)
	Mtl* pMtl = pNode->GetMtl();
	if (pMtl != NULL)
	{
		bool bAdd = true;
		for (int iCnt = 0; iCnt < m_pMtlList.size(); iCnt++)
		{
			if (m_pMtlList[iCnt] == pMtl)
			{
				bAdd = false;
				break;
			}
		}
		if(bAdd)
		{
			m_pMtlList.push_back(pMtl);
		}
	}
}
int S_Global::GetMtlRef(Mtl* pMtl)
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		if (m_pMtlList[iMtl] == pMtl)
		{
			return iMtl;
		}
	}
	return -1;
}

TCHAR* S_Global::FixupName(MSTR name)
{
	memset(m_tmpBuffer, 0, sizeof(TCHAR)*MAX_PATH);

	TCHAR* cPtr;
	_tcscpy(m_tmpBuffer, name);
	cPtr = m_tmpBuffer;

	while (*cPtr)
	{
		if (*cPtr == '"') *cPtr = SINGLE_QUOTE;
		else if (*cPtr == ' ' || *cPtr <= CTL_CHARS)
			*cPtr = _T('_');
		cPtr++;
	}
	return m_tmpBuffer;
}

void S_Global::DumpMatrix3(Matrix3* m, D3D_MATRIX& mat)
{
	Point3 row;
	row = m->GetRow(0);
	mat._11 = row.x; mat._13 = row.y; mat._12 = row.z;
	row = m->GetRow(2);
	mat._21 = row.x; mat._23 = row.y; mat._22 = row.z;
	row = m->GetRow(1);
	mat._31 = row.x; mat._33 = row.y; mat._32 = row.z;
	row = m->GetRow(3);
	mat._41 = row.x; mat._43 = row.y; mat._42 = row.z;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
}

void S_Global::DumpPoint3(Point3& pDest, Point3& pSrc)
{
	pDest.x = pSrc.x;
	pDest.y = pSrc.z;
	pDest.z = pSrc.y;
}
bool S_Global::TMNegParity(Matrix3 &m)
{
	return (DotProd(CrossProd(m.GetRow(0), m.GetRow(1)),
		m.GetRow(2)) < 0.0) ? 1 : 0;
}

bool S_Global::EqualPoint2(Point2 p1, Point2 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	return true;
}

bool S_Global::EqualPoint3(Point3 p1, Point3 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;

	return true;
}

bool S_Global::EqualPoint4(Point4 p1, Point4 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;
	if (fabs(p1.w - p2.w) > ALMOST_ZERO)
		return false;
	return true;
}
S_Global::S_Global(void)
{
	m_p3dsMax = NULL;
	m_pRootNode = NULL;
}


S_Global::~S_Global(void)
{
	m_MatrixMap.Release();
}
