#include "S_KHJWriter.h"

void S_KHJWriter::Run()
{
	Exeporter();
}
void S_KHJWriter::GetTexture(Mtl* pmtl, xMtrlerial& xMtrl)
{
	for (int iSubMap=0;iSubMap< pmtl->NumSubTexmaps(); iSubMap++)
	{
		xTextureMap xTexMap;
		Texmap* tex = pmtl->GetSubTexmap(iSubMap);
		if (tex) // tex�� NULL�� �ƴϿ����Ѵ�.
		{
			// ���� ���뿩�� �Ǵ�
			if (pmtl->ClassID() == Class_ID(DMTL_CLASS_ID,0))
			{
				StdMat* std = (StdMat*)pmtl;
				if(std->MapEnabled(iSubMap))
				continue;
			}
			// ���� ���� ���
			if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0)) // bitmap�̴�
			{
				TSTR mapname = ((BitmapTex*)tex)->GetMapName();
				TSTR szFullName;
				TSTR szMapName;
				SplitPathFile(mapname, &szFullName, &szMapName); // max api // szMapName �̰ɿ��Ѵ�!
				xTexMap.iType = iSubMap ;
				xTexMap.name = szMapName;
				xMtrl.m_mapList.push_back(xTexMap);
			}
		}
	}
}
void S_KHJWriter::DumpMatrix3(Matrix3* m, _D3DMATRIX& mat)
{

}
void S_KHJWriter::Exeporter()
{
	m_Scene.iNumObject = m_ObjectList.size();
	m_Scene.iNumMtrl = m_MtrlList.size();

	m_pStream = _tfopen(this->m_szFileName,_T("wt")); // ���� ����
	_ftprintf(m_pStream, _T("%s"), _T("#SCENE"));
		_ftprintf(m_pStream, _T("\n%d %d %d %d %d %d"),
			m_Scene.iFirstFrame,
			m_Scene.iLastFrame,
			m_Scene.iFrameSpeed,
			m_Scene.iTickPerFrame,
			m_Scene.iNumObject,
			m_Scene.iNumMtrl);
		for (int iMtl = 0; iMtl < m_MtrlList.size(); iMtl++)
		{
			xMtrlerial xMtl;
			TSTR calssname;
			m_MtrlList[iMtl]->GetClassName(calssname);
			TSTR name = m_MtrlList[iMtl]->GetName();

			xMtl.m_SubMaterial.resize(m_MtrlList[iMtl]->NumSubMtls());
			if(xMtl.m_SubMaterial.size()>0)
			{
				for (int iSub=0; iSub< xMtl.m_SubMaterial.size();iSub++)
				{
					Mtl* pSubMtl = m_MtrlList[iMtl]->GetSubMtl(iSub);
					GetTexture(pSubMtl,xMtl.m_SubMaterial[iSub]); //sub
				}
			}
			else
			{
				GetTexture(m_MtrlList[iMtl], xMtl); //root
			}
			m_xMtrlList.push_back(xMtl);
		}
		for (int iObj = 0; iObj < m_ObjectList.size(); iObj++) //helper geom
		{
			xGeomMesh xmesh;
			INode* pNode = m_ObjectList[iObj];
			INode* pParent = pNode->GetParentNode;
			xmesh.name = pNode->GetName();
			xmesh.pParentName = _T("none");
			if (!pParent->IsRootNode())// ������ ���
			{
				xmesh.pParentName = pParent->GetName();
				//false �� �Ǿ� ��¥
			}
			// nodetm
			Matrix3 matWorld=pNode->GetNodeTM(m_Interval.Start());
			DumpMatrix3(matWorld, xmesh.matWorld);
			GetMesh(pNode)

			// mtrl_ref
			Mtl* pMtl = m_ObjectList[iObj]->GetMtl();
			int iMtlRef = -1;
			for (int iMtl = 0; iMtl < m_MtrlList.size(); iMtl++)
			{
				if (pMtl == m_MtrlList[iMtl])
				{
					iMtlRef = iMtl;
					// mtlRef ���⿡ �ִ�
				}
			}
			xmesh.mtrlRef = iMtlRef;
			m_xObjectList.push_back(xmesh);
		}
		_ftprintf(m_pStream, _T("\n%s"), _T("#MATERIALE"));
	/*	for (int iMtl = 0; iMtl < m_xMtrlList.size(); iMtl++)
		{
			if (m_xMtrlList[iMtl].m_SubMaterial.size() > 0)
			{
				for (iSub = 0; iSub<)
				for (int iSub = 0; iSub < m_xMtrlList[iMtl].m_mapList.size(); iSub++)
				{
					_ftprintf(m_pStream, _T("\n%d %s"),
						m_xMtrlList[iMtl].m_mapList[iSub].iType,
						m_xMtrlList[iMtl].m_mapList[iSub].name);
				}
			}
		}*/
		

		/*	_ftprintf(m_pStream, _T("%s"), _T("#OBJECT"));
		_ftprintf(m_pStream, _T("\n%d %d %d %d %d %d"),*/

	fclose(m_pStream);
}

void S_KHJWriter::GetMesh(INode* pNode, xGeomMesh& xMesh)
{
	ObjectState os = pNode->EvalWorldState(m_Interval.Start());
	if (!os.obj || os.obj->SuperClassID() != GEOMOBJECT_CLASS_ID)return;

	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(pNode,m_Interval.Start(), needDel);
	if (tri == NULL)return;
	Mesh* mesh = &tri->GetMesh();



	int v0, v1, v2;
	BOOL negScale = TMNegParity(tm);
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
	

	int iNumFace = mesh->getNumFaces();
	for (int iFace = 0; iFace < iNumFace; iFace++)
	{
		Point3 v;
		int iNumVertex = mesh->getNumVerts();
		if(iNumVertex > 0)
		{
			v = mesh->verts[mesh->faces[iFace].v[0]];
			v = mesh->verts[mesh->faces[iFace].v[2]];
			v = mesh->verts[mesh->faces[iFace].v[1]];
		}
		int iNumVertex = mesh->getNumTVerts();
		if (iNumVertex > 0)
		{

		}
		int iNumVertex = mesh->getNumVertCol();
		if (iNumVertex > 0)
		{

		}
		mesh->buildNormals;
	}

	if (needDel)delete tri;
}
void S_KHJWriter::Release()
{

}


S_KHJWriter::S_KHJWriter()
{
}


S_KHJWriter::~S_KHJWriter()
{
}
