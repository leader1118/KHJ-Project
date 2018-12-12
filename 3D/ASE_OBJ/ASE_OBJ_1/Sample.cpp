#pragma once
#include "xCore.h"
#include "x_AseMesh.h"
#include "x_Mesh.h"

class Sample : public xCore
{
public:
	x_AseMesh	m_Obj;
	x_Mesh		m_xObj;
public:
	int IsEqulVertexList(x_Mesh& pMesh,PNCT_VERTEX& v)
	{
		for (int ilist = 0; ilist < pMesh.m_VertexList.size(); ilist++)
		{
			if (v == pMesh.m_VertexList[ilist])
			{
				return ilist;
			}
			return -1;
			// xMesh.m_VertexList
		}

	}
	bool Init()
	{
		if (m_Obj.Load(L"box.ase"))
		{
			for (int iObj = 0; iObj < m_Obj.m_ObjectList.size(); iObj++)
			{
				x_Mesh	xMesh;
				xMesh.m_iNumFaces =
					m_Obj.m_ObjectList[iObj].PosFaceList.size();
				
				xMesh.m_TempVertexList.resize(xMesh.m_iNumFaces*3);

				for (int iFace = 0; iFace < xMesh.m_iNumFaces; iFace++)
				{
					for (int iVer = 0; iVer < 3; iVer++)
					{
						int iID = iFace * 3 + iVer;
						// pos
						if (m_Obj.m_ObjectList[iObj].vertexList.size() > 0)
						{
							int iIndex = m_Obj.m_ObjectList[iObj].PosFaceList[iFace].i[iVer];
							xMesh.m_TempVertexList[iID].p =
								m_Obj.m_ObjectList[iObj].vertexList[iIndex];
						}
						// nor
						if (m_Obj.m_ObjectList[iObj].NorList.size() > 0)
						{
							xMesh.m_TempVertexList[iID].n =
								m_Obj.m_ObjectList[iObj].NorList[iID];
						}
						//color
						xMesh.m_TempVertexList[iID].c = D3DXVECTOR4(1, 1, 1, 1);
						if (m_Obj.m_ObjectList[iObj].ColFaceList.size() > 0)
						{
							int iIndex = m_Obj.m_ObjectList[iObj].ColFaceList[iFace].i[iVer];
													
							xMesh.m_TempVertexList[iID].c.x =
								m_Obj.m_ObjectList[iObj].ColList[iIndex].x;
							xMesh.m_TempVertexList[iID].c.y =
								m_Obj.m_ObjectList[iObj].ColList[iIndex].y;
							xMesh.m_TempVertexList[iID].c.z =
								m_Obj.m_ObjectList[iObj].ColList[iIndex].z;
							xMesh.m_TempVertexList[iID].c.w = 1.0f;
								
						}
						//tex
						if (m_Obj.m_ObjectList[iObj].texFaceList.size() > 0)
						{
							int iIndex = m_Obj.m_ObjectList[iObj].texFaceList[iFace].i[iVer];
							xMesh.m_TempVertexList[iID].t.x =
								m_Obj.m_ObjectList[iObj].texList[iIndex].x;
							xMesh.m_TempVertexList[iID].t.y =
								m_Obj.m_ObjectList[iObj].texList[iIndex].y;
							
						}
					}
				}

				// Create ib + vb
				// xMesh.m_VertexList;
				for (int ivb = 0; ivb < xMesh.m_TempVertexList.size(); ivb++)
				{
					PNCT_VERTEX v = xMesh.m_TempVertexList[ivb];
					int iPos = IsEqulVertexList(xMesh, v);
					if (iPos < 0)
					{
						xMesh.m_VertexList.push_back(v);
						iPos = xMesh.m_VertexList.size() - 1;
					}
					xMesh.m_IndexList.push_back(iPos);
				}
				xMesh.m_iNumIndex = xMesh.m_IndexList.size();
				xMesh.m_iNumVertex = xMesh.m_VertexList.size();

				int iRef = m_Obj.m_ObjectList[iObj].mtrlRef;
				T_STR texName = m_Obj.m_MaterialList[iRef].m_mapList[0].name;
				
				xMesh.Create(m_pd3dDevice,
					L"../../Include/data/Shader/map.hlsl",
					texName);
				//xMesh.m_iNumIndex = xMesh.m_iNumVertex;
				m_xObj.m_ObjectList.push_back(xMesh);
			}
		}
		return true;
	}
	bool Render()
	{
		for (auto mesh : m_xObj.m_ObjectList)
		{
			mesh.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
			mesh.Render(m_pContext);

		}
		return true;
	}
	bool Release()
	{
		for (auto mesh : m_xObj.m_ObjectList)
		{
			mesh.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
			mesh.Release();
		}
		return true;
	}
	
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SAMPLE_ASE", 800, 600)