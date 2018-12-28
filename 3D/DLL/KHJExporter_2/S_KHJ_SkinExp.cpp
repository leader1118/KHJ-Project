#include "S_KHJ_SkinExp.h"
#include "S_KHJ_Writer.h"

bool S_KHJ_SkinExp::Init()
{
	return true;
}
void S_KHJ_SkinExp::ExportPhysiqueData(INode* node, Modifier *phyMod)
{
	IPhysiqueExport * phyExport = (IPhysiqueExport*)phyMod->GetInterface(I_PHYEXPORT);
	IPhyContextExport * mcExport = (IPhyContextExport *)phyExport->GetContextInterface(node);

	// 블랜딩 및 논블랜딩 타입을 변환
	mcExport->ConvertToRigid(true);
	mcExport->AllowBlending(true);

	// 블랜딩 타입일 경우 변환
	// class UPhyBlendedRigidVertex : public IPhyVertexExport
	IPhyBlendedRigidVertex *rb_vtx = NULL;
	// 논블랜딩 타입일 경우 변환
	// class IPhyRigidVertex : public IPhyVertexExport
	IPhyRigidVertex *r_vtx = NULL;
	int numverts = mcExport->GetNumberVertices();
	// 피직크에 적용이 된 모든 정점들에 대한 정보를 얻는다.
	for (int i = 0; i < numverts; i++)
	{
		float totalWeight = 0.0f, weight = 0.0f;
		TSTR nodeName;

		// 독립된 정점(IPhyVertexExport) 을 얻는다.
		IPhyVertexExport *vi = mcExport->GetVertexInterface(i);
		if (vi)
		{
			// 정점에 적용된 타입을 파악해야 한다.
			int type = vi->GetVertexType();
			switch (type)
			{
				case RIGID_BLENDED_TYPE:
				{
					rb_vtx = (IPhyBlendedRigidVertex*)vi;
					// 현 정점에 영향을 미치는 노드의 갯수
					int iNode = rb_vtx->GetNumberNodes();
					SBipedVertex BipVertex;
					BipVertex.m_dwNumWeight = iNode;

					// Point3 BlendP(0.0f,0.0f,0.0f);
					for (int x = 0; x < iNode; x++)
					{
						INode* pNode = rb_vtx->GetNode(x);
						nodeName = pNode->GetName();
						// 전체 노드를 저장하고 있는 SMatrixExport 에서 해당 인덱스를 리턴 받는다.
						BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
						BipVertex.m_BipIDList.push_back(Index);

						float fWeight = rb_vtx->GetWeight(x);
						BipVertex.m_fWeightList.push_back(fWeight);

						// Point3 Offset=rb_vtx->GetOffsetVector(x);
						// BlendP +=(pNode->GetNodeTM(I_Writer.m_p3dsMax->GetTime())*offset)*fWeight;

						if (Index < 0)
						{
							MessageBox(GetActiveWindow(), _T("No Biped ID."), _T("ERROR !!"), MB_OK | MB_ICONSTOP);
							break;
						}
					}
					// 최대 가중치 갯수를 저장
					if (m_Scene.iMaxweight < iNode)
					{
						m_Scene.iMaxweight = iNode;
						if (m_Scene.iMaxweight > 8)
						{
							MessageBox(GetActiveWindow(), _T("바이패드+ 본 + 더미가 정점 당 8 개 이상 적용되었습니다."), _T("최대 적용 에러"), MB_OK | MB_ICONSTOP);
						}
					}
					m_BipedList.push_back(BipVertex);
				}
				break;
				case RIGID_NON_BLENDED_TYPE:
				{
					r_vtx = (IPhyRigidVertex*)vi;
					// 정점에 적용이 된 노드의 이름을 얻는다.
					INode* pNode = r_vtx->GetNode();
					nodeName = pNode->GetName();

					SBipedVertex BipVertex;
					BipVertex.m_dwNumWeight = 1;
					// 매트릭스 익스포터에서 저장된 모든 노드를 참조해서
					// 현 nodeName과 같은 노드를 찾아서 그 인덱스를 리턴한다.
					BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
					BipVertex.m_BipIDList.push_back(Index);
					BipVertex.m_fWeightList.push_back(1.0f);
					
					// 최대 가중치 갯수를 저장
					if (m_Scene.iMaxweight < 1)
					{
						m_Scene.iMaxweight = 1;
					}
					m_BipedList.push_back(BipVertex);

					if (Index < 0)
					{
						MessageBox(GetActiveWindow(), _T("No Biped ID."), _T("Errror !!"), MB_OK | MB_ICONSTOP);
						break;
					}
				}
				break;
				default:
					MessageBox(GetActiveWindow(), _T("Nothing !! Rigid Vertex Type"), _T("Error !!"), MB_OK | MB_ICONSTOP);
					break;
			}
			mcExport->ReleaseVertexInterface(vi);
		}
	}
	phyExport->ReleaseContextInterface(mcExport);
	phyMod->ReleaseInterface(I_PHYINTERFACE, phyExport);
}

void  S_KHJ_SkinExp::ExportSkinData(INode* node, Modifier *skinMod)
{
	if (node == NULL || skinMod == NULL)return;
	// get the skin interface
	ISkin * skin = (ISkin*)skinMod->GetInterface(I_SKIN);
	ISkinContextData* skinData = skin->GetContextInterface(node);

	if (skin && skinData)
	{
		int numberOFPoints;
		// 스킨 버텍스의 갯수
		numberOFPoints = skinData->GetNumPoints();
		for (int i = 0; i < numberOFPoints; i++)
		{
			// 연결된 본의 갯수
			int numOFWeights = skinData->GetNumAssignedBones(i);

			SBipedVertex BipVertex;
			BipVertex.m_dwNumWeight = numOFWeights;

			for (int j = 0; j < numOFWeights; j++)
			{
				int boneIndex = skinData->GetAssignedBone(i, j);
				INode* pBone = skin->GetBone(boneIndex);
				if (pBone == NULL)break;

				const TCHAR* nodeName = nodeName = pBone->GetName(); //skin - >GetBoneName(boneIndex);
				float boneWeight = skinData->GetBoneWeight(i, j);

				BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
				BipVertex.m_BipIDList.push_back(Index);
				BipVertex.m_fWeightList.push_back(boneWeight);

				if (Index < 0)
				{
					MessageBox(GetActiveWindow(), _T("No Biped ID"), _T("Error!!"), MB_OK | MB_ICONSTOP);
					break;
				}
			}
			m_BipedList.push_back(BipVertex);

			// 최대 가중치 갯수를 저장
			if (m_Scene.iMaxweight < numOFWeights)
			{
				m_Scene.iMaxweight = numOFWeights;
				if (m_Scene.iMaxweight > 8)
				{
					MessageBox(GetActiveWindow(), _T(" 바이패드 + 본 + 더미가 정점 당 8개 이상 적용되었습니다."), _T("최대 적용 에러 !"), MB_OK | MB_ICONSTOP);
				}
			}
		}
	}
}

void S_KHJ_SkinExp::SetBipedInfo(INode* node)
{
	Modifier *phyMod = FindModifier(node, Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B));
	Modifier *skinMod = FindModifier(node, SKIN_CLASSID);
	if (phyMod)
	{
		ExportPhysiqueData(node, phyMod);
	}
	else if (skinMod)
	{
		ExportSkinData(node, skinMod);
	}
}
// 노드에 대한 정보 획득
bool S_KHJ_SkinExp::GetNodeInfo(INode* node, TimeValue t)
{
	// 랜더가능한 데이터 정보 버퍼 저장.
	BOOL needDel;
	TriObject *tri = I_Writer.GetTriObjectFromNode(node, t, needDel);
	if (tri == NULL)return false;

	Mesh * mesh = &tri->GetMesh();
	mesh->buildNormals();
	if (!mesh->faces || !tri || !mesh || !mesh->getNumFaces() || !mesh->getNumVerts() || !mesh->getNumTVerts())
	{
		return false;
	}

	SetBipedInfo(node);

	SSkinMesh* SkinMesh = NULL;
	SAFE_NEW(SkinMesh, SSkinMesh);
	// 메쉬를 저장한다. (서브메터리얼 여부를 판단하여 저장)
	GenerateGroup(node, mesh, SkinMesh);

	if (needDel)
	{
		delete tri;
	}
	return true;
}

void S_KHJ_SkinExp::SetVertexBiped(INode* node, Face* face, int v0, int v1, int v2, SSkinTri* pTri)
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
				pTri->m_vVertex[1].i2[iBip - 4] = m_BipedList[face->v[2]].m_BipIDList[iBip];
				pTri->m_vVertex[1].w2[iBip - 4] = m_BipedList[face->v[2]].m_fWeightList[iBip];
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
		// 정점 당 가중치 적용 갯수
		pTri->m_vVertex[0].w2[3] = m_BipedList[face->v[v0]].m_dwNumWeight;
		pTri->m_vVertex[1].w2[3] = m_BipedList[face->v[v2]].m_dwNumWeight;
		pTri->m_vVertex[2].w2[3] = m_BipedList[face->v[v1]].m_dwNumWeight;
	}
	else
	{
		// 정점에 적용된 바이패드가 없다는 것은 자체 애니메이션을 가진 오브젝트가 된다.
		// 이때는 가중치를 얻을 수 없기 떄문에 직접 1개의 가중치 값을 세팅해 주어야 한다.
		int iBipIndex = I_Writer.GetIndex(node->GetName());
		pTri->m_vVertex[0].i1[0] = iBipIndex;
		pTri->m_vVertex[0].w1[0] = 1.0f;
		pTri->m_vVertex[1].i1[0] = iBipIndex;
		pTri->m_vVertex[1].w1[0] = 1.0f;
		pTri->m_vVertex[2].i1[0] = iBipIndex;
		pTri->m_vVertex[2].w1[0] = 1.0f;

		// 가중치 적용 갯수
		pTri->m_vVertex[0].w2[3] = 1.0f;
		pTri->m_vVertex[1].w2[3] = 1.0f;
		pTri->m_vVertex[2].w2[3] = 1.0f;
	}
}

void S_KHJ_SkinExp::SetTriangle(INode* node, Mesh* mesh, SSkinMesh* pSkinMesh, SSkinMesh*pSubMesh, int iMtrl)
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

	// 원하는 시점 (I_Writer.m_p3dsMax->GetTime() 에서 월드 행렬을 얻는다.
	Matrix3 tm = node->GetObjTMAfterWSM(I_Writer.m_Interval.Start()); // .m_p3dsMax->GetTime();
	Matrix3 nodetm = node->GetNodeTM(I_Writer.m_Interval.Start());
	I_Writer.DumpMatrix3(&nodetm, pSkinMesh->m_matWorld);

	int v0, v1, v2;
	v0 = 0, v1 = 1, v2 = 2;
	if (I_Writer.TMNegParity(tm))
	{
		v0 = 2, v1 = 1, v2 = 2;
	}
}

S_KHJ_SkinExp::S_KHJ_SkinExp()
{
}


S_KHJ_SkinExp::~S_KHJ_SkinExp()
{
}
