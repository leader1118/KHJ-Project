#include "S_KHJGlobal.h"



void S_KHJGlobal::Initialize(Interface *i, TSTR name)
{
	m_pMax = i;
	m_szFileName = name;
	m_pRootNode = m_pMax->GetRootNode();
	m_Interval = m_pMax->GetAnimRange();
	m_Scene.iFirstFrame = m_Interval.Start() / GetTicksPerFrame();
	m_Scene.iLastFrame = m_Interval.End() / GetTicksPerFrame();
	m_Scene.iFrameSpeed = GetFrameRate();
	m_Scene.iTickPerFrame = GetTicksPerFrame(); // ����/ 160

	PreProcess(m_pRootNode);
}
void S_KHJGlobal::AddObject(INode*pNode)
{
	ObjectState os = pNode->EvalWorldState( // ������Ʈ ����
	m_Interval.Start());
	if (os.obj)
	{
		switch (os.obj->SuperClassID())
		{
		case GEOMOBJECT_CLASS_ID:
		case HELPER_CLASS_ID:
			//geomobject
			//helperobject
			m_ObjectList.push_back(pNode);
		}
	}
}
void S_KHJGlobal::AddMtl(INode*pNode)
{
	Mtl* pMtl = pNode->GetMtl();
	if (pMtl != NULL) // NULL �� ���� �ʴٸ� �ִ�
	{
		bool bAdd = true; // flag ��
		for (int iCnt = 0; iCnt <m_MtrlList.size(); iCnt++)
		{
			if (m_MtrlList[iCnt] == pMtl)
			{
				bAdd = false;
				break;
			}
		}
		if (bAdd)
		{
			m_MtrlList.push_back(pMtl);
		}
	}
}
void S_KHJGlobal::PreProcess(INode* pNode)
{
	if (pNode == NULL)return;
	AddObject(pNode);
	AddMtl(pNode);
	int iNumChild = pNode->NumberOfChildren();
	for (int iChild = 0; iChild < iNumChild; iChild++)
	{
		INode* pChild = pNode->GetChildNode(iChild);
		PreProcess(pChild);
	}
}
S_KHJGlobal::S_KHJGlobal()
{
}


S_KHJGlobal::~S_KHJGlobal()
{
}
