#include "S_KHJ_Global.h"

int S_KHJ_Global::GetIndex(const TCHAR* strNodeName)
{
	return m_MatrixMap.GetID(strNodeName);
}

bool S_KHJ_Global::CheckFile(Interface* pMax)
{
	TSTR curtFileName = FixupName(pMax->GetCurFileName());
	if (curtFileName.isNull() == false && m_CurtFileName == curtFileName)
	{
		return false;
	}

	m_MatrixMap.Release();
	m_pMtlList.clear(); // ���͸��� ����Ʈ

	m_CurtFileName = curtFileName;
	return true;
}

bool S_KHJ_Global::Initialize(Interface* pMax)
{
	m_p3dsMax = pMax;
	m_pRootNode = pMax->GetRootNode();

	if (pMax == NULL && m_pRootNode == NULL)
	{
		return false;
	}
	if (CheckFile(pMax) == false)return true;

	// Scene  ���� ���
	m_Interval = m_p3dsMax->GetAnimRange();

	m_Scene.iNumMesh = m_MatrixMap.Count();
	m_Scene.iMaxweight = 1;
	return true;
}
void S_KHJ_Global::PreProcess(INode* pNode)
{
	if (pNode == NULL)return;
	AddObject(pNode);
	AddMtl(pNode);

	// ��� ȣ��
	int iNumChildren = pNode->NumberOfChildren(); // pNode�� �ڽ� ��� ������ ��ȯ��.

	for (int iCnt = 0; iCnt < iNumChildren; iCnt++)
	{
		INode* pChild = pNode->GetChildNode(iCnt); // iCnt ��°�� �ڽ� ��带 ��ȯ��.
		PreProcess(pChild);
	}
}

void S_KHJ_Global::AddObject(INode* pNode)
{
	// ������ Ʈ �߰�
	ObjectState os = pNode->EvalWorldState(m_Interval.Start());
	// Ÿ�� Ŭ������ ������Ʈ�� ���ʿ��� ������Ʈ�̴�.
	if (os.obj)
	{
		// Ÿ��Ŭ������ ������Ʈ�� ���ʿ��� ������Ʈ�̴�.
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
		{
			return;
		}
		switch (os.obj->SuperClassID)
		{
		case GEOMOBJECT_CLASS_ID:
			case HELPER_CLASS_ID:
			{
				int iIndex = m_MatrixMap.Add(pNode->GetName());
				TSTR parentName = pNode->GetParentNode()->GetName();
				m_MatrixMap.GetPtr(iIndex)->SetNode(pNode, m_Interval.Start(), m_MatrixMap.GetPtr(parentName));
			}
			break;
		}
	}
}

void S_KHJ_Global::AddMtl(INode* pNode)
{
	// ���͸��� �߰� (�ߺ�����)
	Mtl* pMtl = pNode->GetMtl();
	if (pMtl != NULL)
	{
		bool bAdd = true;
		for (int iCnt = 0; iCnt < m_pMtlList.size(); iCnt++)
		{
			if (m_pMtlList[iCnt] == pMtl)// �ߺ�����
			{
				bAdd = false;
				break;
			}
		}
		if (bAdd)
		{
			m_pMtlList.push_back(pMtl);
		}
	}
}

int S_KHJ_Global::GetMtlref(Mtl* pMtl) // ���͸��� ���۷��� ����
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

TCHAR* S_KHJ_Global::FixupName(MSTR name)
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

void S_KHJ_Global::DumpMatrix3(Matrix3* m, D3D_MATRIX& mat)
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

void S_KHJ_Global::DumpPoint3(Point3& pDest, Point3& pSrc)
{
	pDest.x = pSrc.x;
	pDest.y = pSrc.z;
	pDest.z = pSrc.y;
}

bool S_KHJ_Global::TMNegParity(Matrix3 &m)
{
	return (DotProd(CrossProd(m.GetRow(0), m.GetRow(1)),
		m.GetRow(2)) < 0.0f) ? 1 : 0;
}

bool S_KHJ_Global::EqualPoint2(Point2 p1, Point2 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	return true;
}
bool S_KHJ_Global::EqualPoint3(Point3 p1, Point3 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;
	return true;
}

bool S_KHJ_Global::EqualPoint4(Point4 p1, Point4 p2)
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
S_KHJ_Global::S_KHJ_Global(void)
{
	m_p3dsMax = NULL; // �ƽ� �������̽�
	m_pRootNode = NULL;
}


S_KHJ_Global::~S_KHJ_Global(void)
{
	m_MatrixMap.Release();
}