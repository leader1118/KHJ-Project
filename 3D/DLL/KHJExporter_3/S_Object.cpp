#include "S_Object.h"

void S_Object::GetMaterial()
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		Mtl* pSrcMtl = m_pMtlList[iMtl];

		SMtl AddMtl;
		TSTR className;
		pSrcMtl->GetClassName(className);
		AddMtl.strName = FixupName(pSrcMtl->GetName());
		AddMtl.strClassname = FixupName(className);
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
				AddSubMtl.strClassname = FixupName(className);

				if (subMtl->NumSubMtls() > 0)
				{
					MessageBox(0, _T(" 다중 서브 매터리얼"), _T("Fatal error"), MB_OK);
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

void S_Object::GetTexture(SMtl* DestMtrl, Mtl* pSrcMtl)
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
				TexMap.strTextureName = FixupName(mapName);
			}
			DestMtrl->TexMaps.push_back(TexMap);
			DestMtrl->iNumMap = DestMtrl->TexMaps.size();
		}
	}
}

void S_Object::UpdateObject()
{
	for (int iObj = 0; iObj < m_MatrixMap.Count(); iObj++)
	{
		MATRIXINDEX* pPoint = (MATRIXINDEX*)m_MatrixMap.TMap[iObj];
		GetObject(pPoint);
	}
}

void S_Object::GetObject(MATRIXINDEX* pPoint)
{
	SMesh* pMesh = &pPoint->m_tMesh;
	pMesh->m_ClassType = pPoint->m_ClassType;
	GetNodeHeader(pPoint->m_pINode, pMesh); // 노드의 이름
	GetNodeTM(pPoint->m_pINode, pMesh); // 노드의 행렬
	GetMesh(pPoint->m_pINode, pMesh); // 기하 정보
	GetAnimKeys(pPoint->m_pINode, pMesh); // 애니메이션 정보
}


void S_Object::GetNodeHeader(INode* node, SMesh* sMesh)
{
	sMesh->m_strNodeName = FixupName(node->GetName());
	INode* parent = node->GetParentNode();
	if (parent && (!parent->IsRootNode()))
	{
		sMesh->m_strParentName = FixupName(parent->GetName());
	}
}
void S_Object::GetNodeTM(INode* node, SMesh* sMesh)
{
	Matrix3 g_matWorld = node->GetNodeTM(m_Interval.Start());
	DumpMatrix3(&g_matWorld, sMesh->m_matWorld);
}

void S_Object::GetMesh(INode* node, SMesh* sMesh)
{
	Matrix3 tm = node->GetObjTMAfterWSM(m_Interval.Start());

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

	mesh->buildBoundingBox();
	Box3 box = mesh->getBoundingBox(&tm);
	DumpPoint3(sMesh->m_Box.pmax, box.pmax);
	DumpPoint3(sMesh->m_Box.pmin, box.pmin);

	sMesh->m_iNumFace = mesh->getNumFaces();

	BOOL negScale = TMNegParity(tm);
	int v0, v1, v2;
	if (negScale) { v0 = 2; v1 = 1; v2 = 0; }
	else { v0 = 0; v1 = 1; v2 = 2; }

	sMesh->m_TriList.resize(sMesh->m_iNumFace);
	for (int iFace = 0; iFace < sMesh->m_iNumFace; iFace++)
	{
		Matrix3 pInverse = Inverse(node->GetNodeTM(m_Interval.Start()));

		Point3 v;
		//Point3 vv;


		if (mesh->getNumVerts() > 0)
		{
			


			v = mesh->verts[mesh->faces[iFace].v[v0]] * tm * pInverse;
			DumpPoint3(sMesh->m_TriList[iFace].v[0].p, v);

			v = mesh->verts[mesh->faces[iFace].v[v2]] * tm * pInverse;
			DumpPoint3(sMesh->m_TriList[iFace].v[1].p, v);

			v = mesh->verts[mesh->faces[iFace].v[v1]] * tm * pInverse;
			DumpPoint3(sMesh->m_TriList[iFace].v[2].p, v);
		}
		if (mesh->getNumTVerts() > 0)
		{
			sMesh->m_TriList[iFace].v[0].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v0]].x;
			sMesh->m_TriList[iFace].v[0].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v0]].y;
			sMesh->m_TriList[iFace].v[1].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v2]].x;
			sMesh->m_TriList[iFace].v[1].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v2]].y;
			sMesh->m_TriList[iFace].v[2].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v1]].x;
			sMesh->m_TriList[iFace].v[2].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v1]].y;
		}

		sMesh->m_TriList[iFace].v[0].c = Point4(1, 1, 1, 1);
		sMesh->m_TriList[iFace].v[1].c = Point4(1, 1, 1, 1);
		sMesh->m_TriList[iFace].v[2].c = Point4(1, 1, 1, 1);

		if (mesh->getNumVertCol() > 0)
		{
			sMesh->m_TriList[iFace].v[0].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v0]].x;
			sMesh->m_TriList[iFace].v[0].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v0]].y;
			sMesh->m_TriList[iFace].v[0].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v0]].z;
			sMesh->m_TriList[iFace].v[0].c.w = 1.0f;
			sMesh->m_TriList[iFace].v[1].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v2]].x;
			sMesh->m_TriList[iFace].v[1].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v2]].y;
			sMesh->m_TriList[iFace].v[1].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v2]].z;
			sMesh->m_TriList[iFace].v[1].c.w = 1.0f;
			sMesh->m_TriList[iFace].v[2].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v1]].x;
			sMesh->m_TriList[iFace].v[2].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v1]].y;
			sMesh->m_TriList[iFace].v[2].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v1]].z;
			sMesh->m_TriList[iFace].v[2].c.w = 1.0f;
		}

		// 정점 노말 얻기
		mesh->buildNormals();

		int  vert = mesh->faces[iFace].getVert(v0);
		Point3 vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(sMesh->m_TriList[iFace].v[0].n, vn);

		vert = mesh->faces[iFace].getVert(v2);
		vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(sMesh->m_TriList[iFace].v[1].n, vn);

		vert = mesh->faces[iFace].getVert(v1);
		vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(sMesh->m_TriList[iFace].v[2].n, vn);

		// 서브 매터리얼 인덱스
		sMesh->m_TriList[iFace].iSubIndex = mesh->faces[iFace].getMatID();
	}
	if (needDel)
	{
		delete tri;
	}

	sMesh->m_iMtrlRef = GetMtlRef(node->GetMtl());
}

Point3 S_Object::GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv)
{
	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;
	int numNormals = rv->rFlags&NORCT_MASK;
	Point3 vertexnormal;

	if (rv->rFlags& SPECIFIED_NORMAL)
	{
		vertexnormal = rv->rn.getNormal();
	}
	else if (numNormals&& smGroup)
	{
		if (numNormals == 1)
		{
			vertexnormal = rv->rn.getNormal();
		}
		else
		{
			for (int i = 0; i < numNormals; i++)
			{
				if (rv->ern[i].getSmGroup()&smGroup)
				{
					vertexnormal = rv->ern[i].getNormal();

				}
			}
		}
	}
	else
	{
		vertexnormal = mesh->getFaceNormal(faceNo);
	}
	return vertexnormal;
}

TriObject* S_Object::GetTriObjectFromNode(INode* node, TimeValue t, int &deletelt)
{
	deletelt = FALSE;
	Object* obj = node->EvalWorldState(t).obj;
	if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
	{
		TriObject* tri = (TriObject*)obj->ConvertToType(t, Class_ID(TRIOBJ_CLASS_ID, 0));
		if (obj != tri)deletelt = TRUE;
		return tri;
	}
	else
	{
		return NULL;
	}
}
S_Object::S_Object(void)
{
}


S_Object::~S_Object(void)
{
}
