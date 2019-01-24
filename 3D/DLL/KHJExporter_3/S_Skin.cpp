#include "S_Skin.h"
#include "S_Writer.h"

bool S_Skin::Init()
{
	return true;
}
void S_Skin::ExportPhysiqueData(INode* node, Modifier	*phyMod)
{
	IPhysiqueExport *phyExport = (IPhysiqueExport *)phyMod->GetInterface(I_PHYEXPORT);
	IPhyContextExport *mcExport = (IPhyContextExport *)phyExport->GetContextInterface(node);

	// ����  �� ����� Ÿ���� ��ȯ
	mcExport->ConvertToRigid(true);
	mcExport->AllowBlending(true);

	// ���� Ÿ���� ��� ��ȯ
	// class IPhyBlendedRigidVertex : public IPhyVertexExport
	IPhyBlendedRigidVertex	*rb_vtx = NULL;
	// ����� Ÿ���� ��� ��ȯ
	// class IPhyRigidVertex : public IPhyVertexExport
	IPhyRigidVertex			*r_vtx = NULL;
	int numverts = mcExport->GetNumberVertices();
	// ����ũ�� ������ �� ��� �����鿡 ���� ������ ��´�.
	for (int i = 0; i < numverts; i++)
	{
		float totalWeight = 0.0f, weight = 0.0f;
		TSTR nodeName;

		// ������ ����( IPhyVertexExport ) �� ���´�.
		IPhyVertexExport *vi = mcExport->GetVertexInterface(i);
		if (vi)
		{
			// ������ ����� Ÿ���� �ľ��ؾ� �Ѵ�.
			int type = vi->GetVertexType();
			switch (type)
			{
			case RIGID_BLENDED_TYPE:
			{
				rb_vtx = (IPhyBlendedRigidVertex*)vi;
				// �� ������ ������ ��ġ�� ����� ����
				int iNode = rb_vtx->GetNumberNodes();
				SBipedVertex BipVertex;
				BipVertex.m_dwNumWeight = iNode;

				//Point3 BlendP(0.0f, 0.0f, 0.0f);
				for (int x = 0; x < iNode; x++)
				{
					INode* pNode = rb_vtx->GetNode(x);
					nodeName = pNode->GetName();
					// ��ü ��带 �����ϰ� �ִ� TMatrixExport���� �ش� �ε����� ���Ϲ޴´�.
					BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
					BipVertex.m_BipIDList.push_back(Index);

					float fWeight = rb_vtx->GetWeight(x);
					BipVertex.m_fWeightList.push_back(fWeight);

					/*Point3 Offset = rb_vtx->GetOffsetVector(x);
					BlendP += (pNode->GetNodeTM(I_Writer.m_p3dsMax->GetTime()) * Offset) * fWeight;*/

					if (Index < 0)
					{
						MessageBox(GetActiveWindow(), _T("No Biped ID."), _T("ERROR!!"), MB_OK | MB_ICONSTOP);
						break;
					}
				}
				// �ִ� ����ġ ������ ����
				if (m_Scene.iMaxWeight < iNode)
				{
					m_Scene.iMaxWeight = iNode;
					if (m_Scene.iMaxWeight > 8)
					{
						MessageBox(GetActiveWindow(), _T("�����е�+��+���̰� ���� �� 8�� �̻� ����Ǿ����ϴ�."), _T("�ִ� ���� ����!"), MB_OK | MB_ICONSTOP);
					}
				}
				m_BipedList.push_back(BipVertex);
			}
			break;
			case RIGID_NON_BLENDED_TYPE:	//(RIGID_TYPE)		
			{
				r_vtx = (IPhyRigidVertex*)vi;
				// ������ ������ �� ����� �̸��� ��´�.
				INode* pNode = r_vtx->GetNode();
				nodeName = pNode->GetName();

				SBipedVertex BipVertex;
				BipVertex.m_dwNumWeight = 1;
				//��Ʈ���� �ͽ����Ϳ��� ����� ��� ��带 �����ؼ�
				// �� nodeName�� ���� ��带 ã�Ƽ� �� �ε����� �����Ѵ�.
				BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
				BipVertex.m_BipIDList.push_back(Index);
				BipVertex.m_fWeightList.push_back(1.0f);

				// �ִ� ����ġ ������ ����
				if (m_Scene.iMaxWeight < 1)
				{
					m_Scene.iMaxWeight = 1;
				}
				m_BipedList.push_back(BipVertex);

				if (Index < 0)
				{
					MessageBox(GetActiveWindow(), _T("No Biped ID."), _T("ERROR!!"), MB_OK | MB_ICONSTOP);
					break;
				}
			}
			break;
			default:
				MessageBox(GetActiveWindow(), _T("Nothing!! Rigid Vertex Type"), _T("ERROR!!"), MB_OK | MB_ICONSTOP);
				break;
			}
			mcExport->ReleaseVertexInterface(vi);
		}
	}
	phyExport->ReleaseContextInterface(mcExport);
	phyMod->ReleaseInterface(I_PHYINTERFACE, phyExport);

}


void S_Skin::ExportSkinData(INode* node, Modifier *skinMod)
{
	if (node == NULL || skinMod == NULL) return;
	//get the skin interface
	ISkin *skin = (ISkin *)skinMod->GetInterface(I_SKIN);
	ISkinContextData *skinData = skin->GetContextInterface(node);

	if (skin && skinData)
	{
		int numberOfPoints;
		// ��Ų���ؽ��� ����
		numberOfPoints = skinData->GetNumPoints();
		for (int i = 0; i < numberOfPoints; i++)
		{
			// ����� ���� ����
			int numOfWeights = skinData->GetNumAssignedBones(i);

			SBipedVertex BipVertex;
			BipVertex.m_dwNumWeight = numOfWeights;

			for (int j = 0; j < numOfWeights; j++)
			{
				int boneIndex = skinData->GetAssignedBone(i, j);
				INode * pBone = skin->GetBone(boneIndex);
				if (pBone == NULL)  break;
				const TCHAR* nodeName = nodeName = pBone->GetName();					
				float boneWeight = skinData->GetBoneWeight(i, j);

				BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
				BipVertex.m_BipIDList.push_back(Index);
				BipVertex.m_fWeightList.push_back(boneWeight);


				if (Index < 0)
				{
					MessageBox(GetActiveWindow(), _T("No Biped ID."), _T("ERROR!!"), MB_OK | MB_ICONSTOP);
					break;
				}
			}
			m_BipedList.push_back(BipVertex);

			// �ִ� ����ġ ������ ����
			if (m_Scene.iMaxWeight < numOfWeights)
			{
				m_Scene.iMaxWeight = numOfWeights;
				if (m_Scene.iMaxWeight > 8)
				{
					MessageBox(GetActiveWindow(), _T("�����е�+��+���̰� ���� �� 8�� �̻� ����Ǿ����ϴ�."), _T("�ִ� ���� ����!"), MB_OK | MB_ICONSTOP);
				}
			}
		}
	}
}

void S_Skin::SetBipedInfo(INode* node)
{
	Modifier	*phyMod = FindModifier(node, Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B));
	Modifier	*skinMod = FindModifier(node, SKIN_CLASSID);

	if (phyMod)
	{
		ExportPhysiqueData(node, phyMod);
	}
	else if (skinMod)
	{
		ExportSkinData(node, skinMod);
	}
}

bool S_Skin::GetNodeInfo(INode* node, TimeValue t)
{
	BOOL needDel;
	TriObject	*tri = I_Writer.GetTriObjectFromNode(node, t, needDel);
	if (tri == NULL) return false;

	Mesh		*mesh = &tri->GetMesh();
	mesh->buildNormals();
	if (!mesh->faces || !tri || !mesh || !mesh->getNumFaces() || !mesh->getNumVerts() || !mesh->getNumTVerts())
	{
		return false;
	}

	SetBipedInfo(node);

	SSkinMesh*	SkinMesh = NULL;
	SAFE_NEW(SkinMesh, SSkinMesh);
	// �޽��� �����Ѵ�.( ������͸��� ���θ� �Ǵ��Ͽ� ����)
	GenerateGroup(node, mesh, SkinMesh);

	m_SkinmeshList.push_back(SkinMesh);

	if (needDel)
	{
		delete tri;
	}
	return true;
}

void S_Skin::SetVertexBiped(INode* node, Face* face, int v0, int v1, int v2, SSkinTri* pTri)
{
	int iNumWeight = 1;
	if (m_BipedList.size())
	{
		iNumWeight = m_BipedList[face->v[v0]].m_BipIDList.size();
		for (int iBip = 0; iBip < iNumWeight; iBip++)
		{
			if (iBip < 4)
			{
				pTri->m_vVertex[0].i1[iBip] = m_BipedList[face->v[v0]].m_BipIDList[iBip];
				pTri->m_vVertex[0].w1[iBip] = m_BipedList[face->v[v0]].m_fWeightList[iBip];
			}
			else
			{
				pTri->m_vVertex[0].i2[iBip - 4] = m_BipedList[face->v[v0]].m_BipIDList[iBip];
				pTri->m_vVertex[0].w2[iBip - 4] = m_BipedList[face->v[v0]].m_fWeightList[iBip];
			}
		}
		iNumWeight = m_BipedList[face->v[v2]].m_BipIDList.size();
		for (int iBip = 0; iBip < iNumWeight; iBip++)
		{
			if (iBip < 4)
			{
				pTri->m_vVertex[1].i1[iBip] = m_BipedList[face->v[v2]].m_BipIDList[iBip];
				pTri->m_vVertex[1].w1[iBip] = m_BipedList[face->v[v2]].m_fWeightList[iBip];
			}
			else
			{
				pTri->m_vVertex[1].i2[iBip - 4] = m_BipedList[face->v[v2]].m_BipIDList[iBip];
				pTri->m_vVertex[1].w2[iBip - 4] = m_BipedList[face->v[v2]].m_fWeightList[iBip];
			}
		}
		iNumWeight = m_BipedList[face->v[v1]].m_BipIDList.size();
		for (int iBip = 0; iBip < iNumWeight; iBip++)
		{
			if (iBip < 4)
			{
				pTri->m_vVertex[2].i1[iBip] = m_BipedList[face->v[v1]].m_BipIDList[iBip];
				pTri->m_vVertex[2].w1[iBip] = m_BipedList[face->v[v1]].m_fWeightList[iBip];
			}
			else
			{
				pTri->m_vVertex[2].i2[iBip - 4] = m_BipedList[face->v[v1]].m_BipIDList[iBip];
				pTri->m_vVertex[2].w2[iBip - 4] = m_BipedList[face->v[v1]].m_fWeightList[iBip];
			}
		}
		
		pTri->m_vVertex[0].w2[3] = m_BipedList[face->v[v0]].m_dwNumWeight;
		pTri->m_vVertex[1].w2[3] = m_BipedList[face->v[v2]].m_dwNumWeight;
		pTri->m_vVertex[2].w2[3] = m_BipedList[face->v[v1]].m_dwNumWeight;
	}
	else
	{
		
		int iBipIndex = I_Writer.GetIndex(node->GetName());
		pTri->m_vVertex[0].i1[0] = iBipIndex;
		pTri->m_vVertex[0].w1[0] = 1.0f;
		pTri->m_vVertex[1].i1[0] = iBipIndex;
		pTri->m_vVertex[1].w1[0] = 1.0f;
		pTri->m_vVertex[2].i1[0] = iBipIndex;
		pTri->m_vVertex[2].w1[0] = 1.0f;
		
		pTri->m_vVertex[0].w2[3] = 1.0f;
		pTri->m_vVertex[1].w2[3] = 1.0f;
		pTri->m_vVertex[2].w2[3] = 1.0f;
	}
}

void S_Skin::SetTriangle(INode* node, Mesh* mesh, SSkinMesh* pSkinMesh, SSkinMesh* pSubMesh, int iMtrl)
{
	SSkinMesh* pMesh = NULL;
	if (pSubMesh == NULL)
	{
		pMesh = pSkinMesh;
	}
	else
	{
		pMesh = pSubMesh;
	}

	// ���ϴ� ����(I_Writer.m_p3dsMax->GetTime()���� ��������� ��´�. 
	Matrix3		tm = node->GetObjTMAfterWSM(I_Writer.m_Interval.Start());// .m_p3dsMax->GetTime());
	Matrix3		nodetm = node->GetNodeTM(I_Writer.m_Interval.Start());
	I_Writer.DumpMatrix3(&nodetm, pSkinMesh->m_matWorld);

	int v0, v1, v2;
	v0 = 0, v1 = 1, v2 = 2;
	if (I_Writer.TMNegParity(tm))
	{
		v0 = 2, v1 = 1, v2 = 0;
	}
	Matrix3 invTM = Inverse(nodetm);
	for (int i = 0; i < mesh->getNumFaces(); i++)
	{
		// ������͸��� ���ô� �׷�ȭ �ؾ��ϱ� ������ �ش� ���͸����� �ƴҽ� �ݺ���Ŵ
		if (pMesh->m_iMtrlRef > 0 && mesh->faces[i].getMatID() != iMtrl)
		{
			continue;
		}

		SSkinTri Triangle;
		// ���̽� ����Ʈ �ʱ�ȭ
		memset(&Triangle, 0, sizeof(STri));
		// ������͸��� �ε���
		Triangle.iSubIndex = mesh->faces[i].getMatID();

		// ���� ��ġ ����
		if (mesh->getNumVerts() > 0)
		{
			SetVertexBiped(node, &mesh->faces[i], v0, v1, v2, &Triangle);
			for (int iVertex = 0; iVertex < 3; iVertex++)
			{
				Point3 v;
				if (iVertex == 0)		v = tm * mesh->verts[mesh->faces[i].v[v0]];
				else if (iVertex == 1)	v = tm * mesh->verts[mesh->faces[i].v[v2]];
				else					v = tm * mesh->verts[mesh->faces[i].v[v1]];
				//v = invTM * v;
				Triangle.m_vVertex[iVertex].p.x = v.x;
				Triangle.m_vVertex[iVertex].p.y = v.z;
				Triangle.m_vVertex[iVertex].p.z = v.y;
			}
		}

		// ���� �ؽ�����ǥ ����
		if (mesh->getNumTVerts() > 0)
		{
			Triangle.m_vVertex[0].t.x = mesh->tVerts[mesh->tvFace[i].t[v0]].x;
			Triangle.m_vVertex[0].t.y = 1.0f - mesh->tVerts[mesh->tvFace[i].t[v0]].y;
			Triangle.m_vVertex[1].t.x = mesh->tVerts[mesh->tvFace[i].t[v2]].x;
			Triangle.m_vVertex[1].t.y = 1.0f - mesh->tVerts[mesh->tvFace[i].t[v2]].y;
			Triangle.m_vVertex[2].t.x = mesh->tVerts[mesh->tvFace[i].t[v1]].x;
			Triangle.m_vVertex[2].t.y = 1.0f - mesh->tVerts[mesh->tvFace[i].t[v1]].y;
		}

		// ���� �÷� ����
		Triangle.m_vVertex[0].c = Point4(1.0f, 1.0f, 1.0f, 1.0f);
		Triangle.m_vVertex[1].c = Point4(1.0f, 1.0f, 1.0f, 1.0f);
		Triangle.m_vVertex[2].c = Point4(1.0f, 1.0f, 1.0f, 1.0f);
		if (mesh->getNumVertCol() > 0)
		{
			Triangle.m_vVertex[0].c.w = 0xff;
			Triangle.m_vVertex[0].c.x = mesh->vertCol[mesh->vcFace[i].t[v0]].x;
			Triangle.m_vVertex[0].c.y = mesh->vertCol[mesh->vcFace[i].t[v0]].y;
			Triangle.m_vVertex[0].c.z = mesh->vertCol[mesh->vcFace[i].t[v0]].z;

			Triangle.m_vVertex[1].c.w = 0xff;
			Triangle.m_vVertex[1].c.x = mesh->vertCol[mesh->vcFace[i].t[v2]].x;
			Triangle.m_vVertex[1].c.y = mesh->vertCol[mesh->vcFace[i].t[v2]].y;
			Triangle.m_vVertex[1].c.z = mesh->vertCol[mesh->vcFace[i].t[v2]].z;

			Triangle.m_vVertex[2].c.w = 0xff;
			Triangle.m_vVertex[2].c.x = mesh->vertCol[mesh->vcFace[i].t[v1]].x;
			Triangle.m_vVertex[2].c.y = mesh->vertCol[mesh->vcFace[i].t[v1]].y;
			Triangle.m_vVertex[2].c.z = mesh->vertCol[mesh->vcFace[i].t[v1]].z;
		}

		// ���� �븻 �� ���̽� �븻 ����
		Point3 vn, fn;  // Vertex normal, Face normal
		int  vert;
		Face* f;

		f = &mesh->faces[i];
		vert = f->getVert(v0);
		vn = I_Writer.GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));

		Triangle.m_vVertex[0].n.x = vn.x;
		Triangle.m_vVertex[0].n.y = vn.z;
		Triangle.m_vVertex[0].n.z = vn.y;
		vert = f->getVert(v2);
		vn = I_Writer.GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));

		Triangle.m_vVertex[1].n.x = vn.x;
		Triangle.m_vVertex[1].n.y = vn.z;
		Triangle.m_vVertex[1].n.z = vn.y;
		vert = f->getVert(v1);
		vn = I_Writer.GetVertexNormal(mesh, i, mesh->getRVertPtr(vert));

		Triangle.m_vVertex[2].n.x = vn.x;
		Triangle.m_vVertex[2].n.y = vn.z;
		Triangle.m_vVertex[2].n.z = vn.y;

		pMesh->m_SkinTriList.push_back(Triangle);
	}
	pMesh->m_iNumFace = pMesh->m_SkinTriList.size();
}

void S_Skin::GenerateGroup(INode* node, Mesh* mesh, SSkinMesh* pSkinMesh)
{
	Mtl* mtl = node->GetMtl();
	pSkinMesh->m_strNodeName = node->GetName();

	if (mtl)
	{
		pSkinMesh->m_iMtrlRef = mtl->NumSubMtls();
	}
	if (pSkinMesh->m_iMtrlRef > 0)
	{
		for (int imtl = 0; imtl < pSkinMesh->m_iMtrlRef; imtl++)
		{
			SSkinMesh* pSubSkinMesh = NULL;
			SAFE_NEW(pSubSkinMesh, SSkinMesh);
			// �ƽ� ������͸��� ���� ����
			Mtl* subMtl = mtl->GetSubMtl(imtl);
			LoadMaterial(pSubSkinMesh, subMtl);
			// �Ž��� �̷�� ���̽�����Ʈ�� �����.
			SetTriangle(node, mesh, pSkinMesh, pSubSkinMesh, imtl);
			pSkinMesh->m_pSubMesh.push_back(pSubSkinMesh);
		}
	}
	else
	{
		LoadMaterial(pSkinMesh, mtl);
		// �Ž��� �̷�� ���̽�����Ʈ�� �����.
		SetTriangle(node, mesh, pSkinMesh);
	}
}

void S_Skin::LoadMaterial(SSkinMesh*	pMesh, Mtl* mtl)
{
	if (mtl)
	{
		pMesh->m_iNumTex = 0;
		memset(pMesh->m_szTexName, 0, sizeof(TCHAR) * 13 * 30);
		for (int i = 0; i < mtl->NumSubTexmaps(); i++)
		{
			Texmap* subTex = mtl->GetSubTexmap(i);
			float amt = 1.0f;
			if (subTex)
			{
				if (mtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
				{
					if (!((StdMat*)mtl)->MapEnabled(i))
						continue;
				}
				if (subTex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
				{
					pMesh->m_iTexType[pMesh->m_iNumTex] = GetMapID(mtl->ClassID(), i);
					TSTR mapName = ((BitmapTex *)subTex)->GetMapName();
					TCHAR Drive[MAX_PATH];
					TCHAR Dir[MAX_PATH];
					TCHAR FName[MAX_PATH];
					TCHAR Ext[MAX_PATH];
					_tsplitpath_s(I_Writer.FixupName(mapName), Drive, Dir, FName, Ext);
					Ext[4] = 0;
					_stprintf_s(pMesh->m_szTexName[pMesh->m_iNumTex], _T("%s%s"), FName, Ext);
					pMesh->m_iNumTex++;
				}
			}
		}
	}
}
Modifier*	S_Skin::FindModifier(INode *nodePtr, Class_ID classID)
{
	Object *ObjectPtr = nodePtr->GetObjectRef();
	if (!ObjectPtr)
	{
		return NULL;
	}
	while (ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID && ObjectPtr)
	{
		IDerivedObject *DerivedObjectPtr = (IDerivedObject *)(ObjectPtr);

		int ModStackIndex = 0;
		while (ModStackIndex < DerivedObjectPtr->NumModifiers())
		{
			Modifier* ModifierPtr = DerivedObjectPtr->GetModifier(ModStackIndex);

			if (ModifierPtr->ClassID() == classID)
			{
				return ModifierPtr;
			}

			ModStackIndex++;
		}
		ObjectPtr = DerivedObjectPtr->GetObjRef();
	}
	return NULL;
}
int S_Skin::GetMapID(Class_ID cid, int subNo)
{
	int iResultIndex = 1;
	if (cid == Class_ID(0, 0))
	{
		iResultIndex = 30;
	}
	else if (cid == Class_ID(DMTL_CLASS_ID, 0))
	{
		switch (subNo)
		{
		case ID_AM: iResultIndex = 0; break;
		case ID_DI: iResultIndex = 1; break;
		case ID_SP: iResultIndex = 2; break;
		case ID_SH: iResultIndex = 3; break;
		case ID_SS: iResultIndex = 4; break;
		case ID_SI: iResultIndex = 5; break;
		case ID_OP: iResultIndex = 6; break;
		case ID_FI: iResultIndex = 7; break;
		case ID_BU: iResultIndex = 8; break;
		case ID_RL: iResultIndex = 9; break;
		case ID_RR: iResultIndex = 10; break;
		}
	}
	else
	{
		iResultIndex = 31;
	}
	return iResultIndex;
}

int S_Skin::IsEqulVertexList(vector<PNCT5_VERTEX>&  VertexArray, PNCT5_VERTEX& Vertex)
{
	for (int iVertex = 0; iVertex < VertexArray.size(); iVertex++)
	{
		if (I_Writer.EqualPoint3(VertexArray[iVertex].p, Vertex.p) &&
			I_Writer.EqualPoint3(VertexArray[iVertex].n, Vertex.n) &&
			I_Writer.EqualPoint4(VertexArray[iVertex].c, Vertex.c) &&
			I_Writer.EqualPoint2(VertexArray[iVertex].t, Vertex.t))
		{
			return iVertex;
		}
	}
	return -1;
}

bool S_Skin::skmExport()
{
	int iSkinMeshCount = m_SkinmeshList.size();
	if (iSkinMeshCount <= 0)
	{
		MessageBox(NULL, _T("����� ������ �����ϴ�."), _T("���ϻ�������"), MB_ICONERROR);
		return FALSE;
	}

	TCHAR  szFile[256] = { 0, };
	_tcscpy(szFile, I_Writer.SaveFileDlg(_T("skm"), _T("TSkinExport")));

	FILE	*fp;
	fp = _tfopen(szFile, _T("wb"));
	if (!fp)
	{
		MessageBox(NULL, _T("������ �������� ���߽��ϴ�."), _T("���ϻ�������"), MB_ICONERROR);
		return FALSE;
	}

	struct tm *newtime;
	time_t aclock;
	time(&aclock);
	newtime = localtime(&aclock);
	fwrite(newtime, sizeof(tm), 1, fp);

	m_Scene.iNumMesh = m_SkinmeshList.size();
	fwrite(&m_Scene, sizeof(SScene), 1, fp);

	for (SSKINMESH_VECTOR::iterator iter = m_SkinmeshList.begin(); iter != m_SkinmeshList.end(); iter++)
	{
		SSkinMesh* pMesh = (*iter);
		TCHAR szName[256] = { 0, };
		TCHAR szParentName[256] = { 0, };
		// ��� �̸�
		int iLen = pMesh->m_strNodeName.Length();
		fwrite(&iLen, sizeof(int), 1, fp);
		if (iLen > 0)
		{
			_tcscpy(szName, pMesh->m_strNodeName);
			fwrite(szName, sizeof(TCHAR)*iLen, 1, fp);
		}

		// ��� �θ� �̸�
		iLen = pMesh->m_strParentName.Length();
		_tcscpy(szParentName, pMesh->m_strParentName);
		fwrite(&iLen, sizeof(int), 1, fp);
		if (iLen > 0)
		{
			fwrite(szParentName, sizeof(TCHAR)*iLen, 1, fp);
		}

		// ���� ���
		fwrite(&pMesh->m_matWorld, sizeof(D3D_MATRIX), 1, fp);

		// ������͸��� ����
		int iRealSubMtrlConter = pMesh->m_pSubMesh.size();
		fwrite(&iRealSubMtrlConter, sizeof(int), 1, fp);

		if (iRealSubMtrlConter <= 0)
		{
			ExportMesh(fp, pMesh);
		}
		else
		{
			for (int iMesh = 0; iMesh < pMesh->m_pSubMesh.size(); iMesh++)
			{
				SSkinMesh* pSubMesh = pMesh->m_pSkinSubMesh[iMesh];
				ExportMesh(fp, pSubMesh);
			}
		}
	}

	// �巹�� ������ �� �����е� ��� ���
	MATRIXINDEX* matIndex;
	D3D_MATRIX d3dMat;
	int iNumMatrix = I_Writer.m_MatrixMap.TMap.size();
	fwrite(&iNumMatrix, sizeof(int), 1, fp);

	for (int iMat = 0; iMat < iNumMatrix; iMat++)
	{
		matIndex = I_Writer.m_MatrixMap.GetPtr(iMat);
		I_Writer.DumpMatrix3(&matIndex->m_InvNodeTM, d3dMat);
		fwrite(&d3dMat, sizeof(D3D_MATRIX), 1, fp);
	}

	fclose(fp);
	Release();
	MessageBox(GetActiveWindow(), szFile, _T("Succeed!!"), MB_OK);
	return true;
}

bool S_Skin::ExportMesh(FILE* fp, SSkinMesh* pMesh)
{
	vector <PNCT5_VERTEX>			VertexArray;
	vector < unsigned int>			IndexArray;
	VertexArray.reserve(pMesh->m_iNumFace * 3);
	IndexArray.reserve(pMesh->m_iNumFace * 3);

	int iPosPushCnt = 0;
	for (int iFace = 0; iFace < pMesh->m_iNumFace; iFace++)
	{
		for (int iCnt = 0; iCnt < 3; iCnt++)
		{
			int iPosReturn = IsEqulVertexList(VertexArray, pMesh->m_SkinTriList[iFace].m_vVertex[iCnt]);
			if (iPosReturn < 0)
			{
				
				VertexArray.push_back(pMesh->m_SkinTriList[iFace].m_vVertex[iCnt]);
				iPosReturn = iPosPushCnt++;
			}
			IndexArray.push_back(iPosReturn);
		}
	}
	pMesh->m_iNumVertex = VertexArray.size();

	fwrite(&pMesh->m_iNumVertex, sizeof(int), 1, fp);
	fwrite(&pMesh->m_iNumFace, sizeof(int), 1, fp);
	fwrite(&pMesh->m_iNumTex, sizeof(int), 1, fp);

	fwrite(&VertexArray.at(0), sizeof(PNCT5_VERTEX)	* VertexArray.size(), 1, fp);
	fwrite(&IndexArray.at(0), sizeof(unsigned int)	* IndexArray.size(), 1, fp);

	for (int itex = 0; itex < pMesh->m_iNumTex; itex++)
	{
		int iLen = _tcslen(pMesh->m_szTexName[itex]);
		fwrite(&iLen, sizeof(int), 1, fp);
		fwrite(&pMesh->m_iTexType[itex], sizeof(int), 1, fp);
		fwrite(pMesh->m_szTexName[itex], sizeof(TCHAR) * iLen, 1, fp);
	}
	return true;
}

bool S_Skin::Release()
{
	m_BipedList.clear();
	for (SSKINMESH_VECTOR::iterator iter = m_SkinmeshList.begin(); iter != m_SkinmeshList.end(); iter++)
	{
		SSkinMesh* pMesh = (*iter);
		if (pMesh->m_iMtrlRef > 0)
		{
			pMesh->m_pSkinSubMesh.clear();
			for (int imtl = 0; imtl < pMesh->m_iMtrlRef; imtl++)
			{
			
			}
		}
		SAFE_DEL(pMesh);
	}
	m_SkinmeshList.clear();
	return true;
}
S_Skin::S_Skin()
{
	Init();
}


S_Skin::~S_Skin()
{
	Release();
}
