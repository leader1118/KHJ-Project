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


S_KHJ_SkinExp::S_KHJ_SkinExp()
{
}


S_KHJ_SkinExp::~S_KHJ_SkinExp()
{
}
