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

	// ���� �� ����� Ÿ���� ��ȯ
	mcExport->ConvertToRigid(true);
	mcExport->AllowBlending(true);

	// ���� Ÿ���� ��� ��ȯ
	// class UPhyBlendedRigidVertex : public IPhyVertexExport
	IPhyBlendedRigidVertex *rb_vtx = NULL;
	// ����� Ÿ���� ��� ��ȯ
	// class IPhyRigidVertex : public IPhyVertexExport
	IPhyRigidVertex *r_vtx = NULL;
	int numverts = mcExport->GetNumberVertices();
	// ����ũ�� ������ �� ��� �����鿡 ���� ������ ��´�.
	for (int i = 0; i < numverts; i++)
	{
		float totalWeight = 0.0f, weight = 0.0f;
		TSTR nodeName;

		// ������ ����(IPhyVertexExport) �� ��´�.
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

					// Point3 BlendP(0.0f,0.0f,0.0f);
					for (int x = 0; x < iNode; x++)
					{
						INode* pNode = rb_vtx->GetNode(x);
						nodeName = pNode->GetName();
						// ��ü ��带 �����ϰ� �ִ� SMatrixExport ���� �ش� �ε����� ���� �޴´�.
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
					// �ִ� ����ġ ������ ����
					if (m_Scene.iMaxweight < iNode)
					{
						m_Scene.iMaxweight = iNode;
						if (m_Scene.iMaxweight > 8)
						{
							MessageBox(GetActiveWindow(), _T("�����е�+ �� + ���̰� ���� �� 8 �� �̻� ����Ǿ����ϴ�."), _T("�ִ� ���� ����"), MB_OK | MB_ICONSTOP);
						}
					}
					m_BipedList.push_back(BipVertex);
				}
				break;
				case RIGID_NON_BLENDED_TYPE:
				{
					r_vtx = (IPhyRigidVertex*)vi;
					// ������ ������ �� ����� �̸��� ��´�.
					INode* pNode = r_vtx->GetNode();
					nodeName = pNode->GetName();

					SBipedVertex BipVertex;
					BipVertex.m_dwNumWeight = 1;
					// ��Ʈ���� �ͽ����Ϳ��� ����� ��� ��带 �����ؼ�
					// �� nodeName�� ���� ��带 ã�Ƽ� �� �ε����� �����Ѵ�.
					BYTE Index = (BYTE)I_Writer.GetIndex(nodeName);
					BipVertex.m_BipIDList.push_back(Index);
					BipVertex.m_fWeightList.push_back(1.0f);
					
					// �ִ� ����ġ ������ ����
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
