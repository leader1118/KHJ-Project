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
			// xMesh.m_VertexList
		}
		return -1;
	}
	bool Init()
	{
		//if(m_Obj.Load(L"../../Sampleinclude/data/multiBox2.ASE"))
		if(m_Obj.Load(L"../../Sampleinclude/data/St02sc00.ASE"))
		//if (m_Obj.Load(L"../../Sampleinclude/data/BOX.ASE"))
		{
			for (int iObj = 0; iObj < m_Obj.m_ObjectList.size(); iObj++)
			{
				x_Mesh	xMesh;
				int iMtrl = m_Obj.m_ObjectList[iObj].mtrlRef;
				int iSubMtrl = m_Obj.m_MaterialList[iMtrl].m_SubMaterial.size();
				if (iSubMtrl > 0)
				{
					//sub Material
					xMesh.m_SubList.resize(iSubMtrl);

					int iNumFace = m_Obj.m_ObjectList[iObj].PosFaceList.size();
					for (int iFace = 0; iFace < iNumFace; iFace++)
					{
						int iSubBuffer = m_Obj.m_ObjectList[iObj].PosFaceList[iFace].iSubMtrl;
						for (int iVer = 0; iVer < 3; iVer++)
						{
							PNCT_VERTEX v;
							int iID = iFace * 3 + iVer;
							// pos
							if (m_Obj.m_ObjectList[iObj].vertexList.size() > 0)
							{
								int iIndex = m_Obj.m_ObjectList[iObj].PosFaceList[iFace].i[iVer];
								v.p =
									m_Obj.m_ObjectList[iObj].vertexList[iIndex];
							}
							// nor
							if (m_Obj.m_ObjectList[iObj].NorList.size() > 0)
							{
								v.n =
									m_Obj.m_ObjectList[iObj].NorList[iID];
							}
							//color
							v.c = D3DXVECTOR4(1, 1, 1, 1);
							if (m_Obj.m_ObjectList[iObj].ColFaceList.size() > 0)
							{
								int iIndex = m_Obj.m_ObjectList[iObj].ColFaceList[iFace].i[iVer];

								v.c.x =
									m_Obj.m_ObjectList[iObj].ColList[iIndex].x;
								v.c.y =
									m_Obj.m_ObjectList[iObj].ColList[iIndex].y;
								v.c.z =
									m_Obj.m_ObjectList[iObj].ColList[iIndex].z;
								v.c.w = 1.0f;

							}
							//tex
							if (m_Obj.m_ObjectList[iObj].texFaceList.size() > 0)
							{
								int iIndex = m_Obj.m_ObjectList[iObj].texFaceList[iFace].i[iVer];
								v.t.x =
									m_Obj.m_ObjectList[iObj].texList[iIndex].x;
								v.t.y =
									m_Obj.m_ObjectList[iObj].texList[iIndex].y;

							}							
							xMesh.m_SubList[iSubBuffer].m_VertexList.push_back(v);
						}
					}

					for (int iSub = 0; iSub < iSubMtrl; iSub++)
					{
						xMesh.m_SubList[iSub].m_iNumVertex = xMesh.m_SubList[iSub].m_VertexList.size();
						T_STR texName = m_Obj.m_MaterialList[iMtrl].m_SubMaterial[iSub].m_mapList[0].name;

						xMesh.m_SubList[iSub].Create(m_pd3dDevice,
							L"../../Sampleinclude/data/Shader/map.hlsl",
							texName);
					}
				}
				else
				{
					xMesh.m_iNumFaces =
						m_Obj.m_ObjectList[iObj].PosFaceList.size();

					xMesh.m_TempVertexList.resize(xMesh.m_iNumFaces * 3);

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
					// 비용이 많아지는 구간
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
					///////////////////////
					xMesh.m_iNumIndex = xMesh.m_IndexList.size();
					xMesh.m_iNumVertex = xMesh.m_VertexList.size();

					int iRef = m_Obj.m_ObjectList[iObj].mtrlRef;
					//T_STR FullPassName = L"../../Sampleinclude/data/";
					T_STR texName = m_Obj.m_MaterialList[iRef].m_mapList[0].name;
					//FullPassName += texName;

					xMesh.Create(m_pd3dDevice,
						L"../../Sampleinclude/data/Shader/map.hlsl",
						texName);
					//xMesh.m_iNumIndex = xMesh.m_iNumVertex;
				}
				m_xObj.m_ObjectList.push_back(xMesh);
			}

		}
		return true;
	}
	bool Render()
	{
		for (auto mesh : m_xObj.m_ObjectList)
		{		 
			if (mesh.m_SubList.size()>0)
			{
				for (int iSubObj = 0; iSubObj < mesh.m_SubList.size(); iSubObj++)
				{
					mesh.m_SubList[iSubObj].SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
					mesh.m_SubList[iSubObj].Render(m_pContext);
				}
			}
			else
			{
				mesh.SetMatrix(NULL, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
				mesh.Render(m_pContext);
			}
		}
		return true;
	}
	bool Release()
	{
		for (auto mesh : m_xObj.m_ObjectList)
		{
			mesh.Release();
		}
		return true;
	}
	
public:
	Sample() {}
	~Sample() {}
};
GAME_RUN("SAMPLE_ASE", 800, 600)