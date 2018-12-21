#include "S_KHJ_Object.h"

void S_KHJ_Object::GetMaterial()
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		Mtl* pSrcMtl = m_pMtlList[iMtl];

		SMtl AddMtl;
		TSTR className;
		pSrcMtl->GetClassName(className);
		AddMtl.strName = FixupName(pSrcMtl->GetName());
		AddMtl.strClassName = FixupName(className);
		AddMtl.iNumSubMtl = pSrcMtl->NumSubMtls();
		AddMtl.iIndex = iMtl;

		if (pSrcMtl->NumSubMtls() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < pSrcMtl->NumSubMtls(); iSubMtrl++)
			{
				Mtl* subMtl = pSrcMtl->GetSubMtl(iSubMtrl);

				SMtl AddSubMtl;
				AddSubMtl.iIndex = iSubMtrl;
				AddSubMtl.iNumSubMtl = subMtl->NumSubMtls();
				AddSubMtl.strName = FixupName(subMtl->GetName());

				TSTR className;
				subMtl->GetClassName(className);
				AddSubMtl.strClassName = FixupName(className);

				if (subMtl->NumSubMtls() > 0)
				{
					MessageBox(0, _T("다중 서브 매터리얼"), _T("Fatal error"), MB_OK);
				}
				if (subMtl)
				{
					GetTexture(&AddSubMtl, subMtl);
				}
				AddMtl.SubMaterial.push_back(AddSubMtl);
			}
		}
		else
		{
			GetTexture(&AddMtl, pSrcMtl);
		}
		m_Material.push_back(AddMtl);
	}
}

void  S_KHJ_Object::GetTexture(SMtl* DestMtrl, Mtl* pSrcMtl)
{
	for (int iSubMap = 0; iSubMap < pSrcMtl->NumSubTexmaps(); iSubMap++)
	{
		Texmap* tex = pSrcMtl->GetSubTexmap(iSubMap);
		if (tex)
		{
			if (pSrcMtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
			{
				StdMat* std = (StdMat*)pSrcMtl;
				if (!std->MapEnabled(iSubMap))
					continue;
			}

			STexMap TexMap;
			TexMap.iType = iSubMap;

			if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
			{
				TSTR mapName = ((BitmapTex*)tex)->GetMapName();
				TSTR strFullName;
				SplitPathFile(mapName, &strFullName, &mapName);
				TexMap.StrTextureName = FixupName(mapName);
			}
			DestMtrl->TexMaps.push_back(TexMap);
			DestMtrl->iNumMap = DestMtrl->TexMaps.size();
		}
	}
}

void S_KHJ_Object::UpdateObject()
{
	for (int iObj; iObj < m_MatrixMap.Count(); iObj++)
	{
		MATRIXINDEX* pPoint = (MATRIXINDEX*)m_MatrixMap.TMap[iObj];
		GetObject(pPoint);
	}
}

void S_KHJ_Object::GetObject(MATRIXINDEX* pPoint)
{
	SMesh* pMesh = &pPoint->m_sMesh;
	pMesh->m_ClassType = pPoint->m_ClassType;
	GetNodeHeader(pPoint->m_pINode, pMesh); // 노드의 이름을 얻는다.
	GetNodeTM(pPoint->m_pINode, pMesh); // 노드의 행렬을 얻는다.
	GetMesh(pPoint->m_pINode, pMesh); // 기하 정보를 얻는다.
	GetAnimKeys(pPoint->m_pINode, pMesh); // 애니메이션 정보를 얻는다.
}

void S_KHJ_Object::GetNodeHeader(INode* node, SMesh* Smesh)
{
	Smesh->m_strNodeName = FixupName(node->GetName());
	INode* parent = node->GetParentNode();
	if (parent && (!parent->IsRootNode()))
	{
		Smesh->m_strParentName = FixupName(parent->GetName());
	}
}

void S_KHJ_Object::GetNodeTM(INode* node, SMesh* Smesh)
{
	Matrix3 g_matWorld = node->GetNodeTM(m_Interval.Start());
	DumpMatrix3(&g_matWorld, Smesh->m_matWorld);
}

void S_KHJ_Object::GetMesh(INode* node, SMesh* Smesh)
{
	Matrix3 tm = node->GetObjTMAfterWSM(m_Interval.Start());
	// 작업중 및 작업완료된 파이프 라인의 결과에 액세스 함으로써 현재 노드의 결과를 돌려준다.
	ObjectState os = node->EvalWorldState(m_Interval.Start());
	if (!os.obj || os.obj->SuperClassID() != GEOMOBJECT_CLASS_ID)
	{
		return;
	}

	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(node, m_Interval.Start(), needDel);
	if (!tri)
	{
		return;
	}

	Mesh* mesh = &tri->GetMesh();
	// 바운딩 박스
	mesh->buildBoundingBox();
	Box3 box = mesh->getBoundingBox(&tm);
	DumpPoint3(Smesh->m_Box.pmax, box.pmax);
	DumpPoint3(Smesh->m_Box.pmin, box.pmin);

	Smesh->m_iNumFace = mesh->getNumFaces();

	BOOL negScale = TMNegParity(tm);
	int v0, v1, v2;
	if (negScale)
	{
		v0 = 2;
		v1 = 1;
		v2 = 0;
	}
	else
	{
		v0 = 0;
		v1 = 1;
		v2 = 2;
	}

	Smesh->m_TriList.resize(Smesh->m_iNumFace);
}
S_KHJ_Object::S_KHJ_Object()
{
}


S_KHJ_Object::~S_KHJ_Object()
{
}
