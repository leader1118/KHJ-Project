#include "x_AseMesh.h"
void   x_AseMesh::LoadScene()
{
	//*SCENE_FILENAME "Box.max"
	_fgetts(m_pBuffer, 256, m_pStream);
	//*SCENE_FIRSTFRAME 0
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iFirstFrame);
	//*SCENE_LASTFRAME 100
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iLastFrame);
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iFrameSpeed);
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iTickPerFrame);
}
void   x_AseMesh::LoadMaterial()
{
	//*MATERIAL_COUNT 1
	int iCount = 0;
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iCount);

	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		xMaterial  xMat;
		xTextureMap  tMap;

		if (FineString(_T("*MAP_SUBNO")) == false) return;

		_stscanf(m_pBuffer, _T("%s%d"), m_pString, &tMap.iType);
		_fgetts(m_pBuffer, 256, m_pStream);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s%s"), m_pString, m_pString2);

		TCHAR drive[256] = { 0, };
		TCHAR dir[256] = { 0, };
		TCHAR fname[256] = { 0, };
		TCHAR ext[256] = { 0, };
		_tsplitpath(m_pString2, drive, dir, fname, ext);

		tMap.name = fname;
		ext[4] = 0;
		tMap.name += ext;
		xMat.m_mapList.push_back(tMap);
		m_MaterialList.push_back(xMat);
	}
}
bool   x_AseMesh::Load(T_STR name)
{
	m_pStream = NULL;
	m_pStream = _tfopen(name.c_str(), _T("rt"));
	if (m_pStream == NULL) return false;
	if (FineString(_T("*SCENE")) == false) return false;
	LoadScene();

	if (FineString(_T("*MATERIAL_LIST")) == false) return false;
	LoadMaterial();

	if (FineString(_T("*GEOMOBJECT")) == false) return false;
	LoadGeomObject();

	fclose(m_pStream);
	return true;
}
void x_AseMesh::GetData(void* pData)
{
	_stscanf(m_pBuffer, _T("%s%f%f%f"),
		m_pString,
		&((D3DXVECTOR3*)pData)->x,
		&((D3DXVECTOR3*)pData)->z,
		&((D3DXVECTOR3*)pData)->y);
}
bool x_AseMesh::FineString(T_STR find)
{
	while (!feof(m_pStream))
	{
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);
		if (!_tcsicmp(m_pString, find.c_str()))
		{
			return true;
		}
	}
	return false;
}
void x_AseMesh::LoadVertexData(D3DXVECTOR3& v, bool bSwap)
{
	_fgetts(m_pBuffer, 256, m_pStream);
	if (bSwap)
	{
		_stscanf(m_pBuffer, _T("%s%d%f%f%f"),
			m_pString,
			&m_iTemp,
			&v.x,
			&v.z,
			&v.y);
	}
	else
	{
		_stscanf(m_pBuffer, _T("%s%d%f%f%f"),
			m_pString,
			&m_iTemp,
			&v.x,
			&v.y,
			&v.z);
	}
}
void x_AseMesh::LoadIndexData(xIndex& v)
{
	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%d%d%d%d"),
		m_pString,
		&m_iTemp,
		&v.i[0],
		&v.i[2],
		&v.i[1]);
}
void x_AseMesh::LoadGeomObject()
{
	
	while (!feof(m_pStream))
	{
		int iNumFaces = 0;
		int iNumVertex = 0;
		xGeomMesh geomObject;
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s%s"), m_pString, m_pString2);
		geomObject.name = m_pString2;

		D3DXMatrixIdentity(&geomObject.matWorld);
		if (FineString(_T("*TM_ROW0")) == false) return;

		GetData(&geomObject.matWorld.m[0]);
		_fgetts(m_pBuffer, 256, m_pStream);
		GetData(&geomObject.matWorld.m[2]);
		_fgetts(m_pBuffer, 256, m_pStream);
		GetData(&geomObject.matWorld.m[1]);
		_fgetts(m_pBuffer, 256, m_pStream);
		GetData(&geomObject.matWorld.m[3]);

		if (FineString(_T("*MESH")) == false) return;

		_fgetts(m_pBuffer, 256, m_pStream);
		//*MESH_NUMVERTEX 8
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumVertex);
		if (iNumVertex > 0)
		{
			//*MESH_NUMFACES 12		
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumFaces);

			_fgetts(m_pBuffer, 256, m_pStream);
			geomObject.vertexList.resize(iNumVertex);
			for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
			{
				LoadVertexData(geomObject.vertexList[iVertex]);
			}
			_fgetts(m_pBuffer, 256, m_pStream);
			_fgetts(m_pBuffer, 256, m_pStream);
			geomObject.PosFaceList.resize(iNumFaces);
			for (int iFace = 0; iFace < iNumFaces; iFace++)
			{
				//*MESH_FACE    0:    A:    0 B:    2 C:    3
				//AB:    1 BC:    1 CA:    0	
				//*MESH_SMOOTHING 2 	*MESH_MTLID 1
				_fgetts(m_pBuffer, 256, m_pStream);
				_stscanf(m_pBuffer, _T("%s%s %s%d %s%d %s%d %s%d %s%d %s %d %s%d %s%d"),
					m_pString, m_pString, m_pString,
					&geomObject.PosFaceList[iFace].i[0],
					m_pString,
					&geomObject.PosFaceList[iFace].i[2],
					m_pString,
					&geomObject.PosFaceList[iFace].i[1],
					m_pString, &m_iTemp,
					m_pString, &m_iTemp,
					m_pString, &m_iTemp,
					m_pString, &m_iTemp,
					m_pString, &geomObject.PosFaceList[iFace].iSubMtrl);
			}
		}
		// Texture Coord
		_fgetts(m_pBuffer, 256, m_pStream);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumVertex);
		if (iNumVertex > 0)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			geomObject.texList.resize(iNumVertex);
			for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
			{
				LoadVertexData(geomObject.texList[iVertex], false);
				geomObject.texList[iVertex].y = 1.0f - geomObject.texList[iVertex].y;

			}
			//*MESH_NUMTVFACES 12
			_fgetts(m_pBuffer, 256, m_pStream);
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumFaces);
			_fgetts(m_pBuffer, 256, m_pStream);
			geomObject.texFaceList.resize(iNumFaces);
			for (int iFace = 0; iFace < iNumFaces; iFace++)
			{
				LoadIndexData(geomObject.texFaceList[iFace]);
			}
		}
		//*MESH_NUMCVERTEX 0
		_fgetts(m_pBuffer, 256, m_pStream);
		_fgetts(m_pBuffer, 256, m_pStream);
		_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumVertex);
		geomObject.ColList.resize(iNumVertex);
		if (iNumVertex > 0)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
			{
				LoadVertexData(geomObject.ColList[iVertex], false);
			}
			//*MESH_CFACELIST 0
			_fgetts(m_pBuffer, 256, m_pStream);
			_fgetts(m_pBuffer, 256, m_pStream);
			_stscanf(m_pBuffer, _T("%s%d"), m_pString, &iNumFaces);

			geomObject.ColFaceList.resize(iNumFaces);
			for (int iFace = 0; iFace < iNumFaces; iFace++)
			{
				LoadIndexData(geomObject.ColFaceList[iFace]);
			}
		}
		//*MESH_NORMALS{
		geomObject.NorList.resize(iNumFaces * 3);
		_fgetts(m_pBuffer, 256, m_pStream);
		for (int iFace = 0; iFace < iNumFaces; iFace++)
		{
			_fgetts(m_pBuffer, 256, m_pStream);
			LoadVertexData(geomObject.NorList[iFace * 3 + 0]);
			LoadVertexData(geomObject.NorList[iFace * 3 + 2]);
			LoadVertexData(geomObject.NorList[iFace * 3 + 1]);
		}
		//*MATERIAL_REF 0
		if (FineString(_T("*MATERIAL_REF")) == false) return;
		_stscanf(m_pBuffer, _T("%s%d"), m_pString, &geomObject.mtrlRef);

		_fgetts(m_pBuffer, 256, m_pStream);
		_fgetts(m_pBuffer, 256, m_pStream);
		m_ObjectList.push_back(geomObject);
	}
}
x_AseMesh::x_AseMesh()
{
}
x_AseMesh::~x_AseMesh()
{
}
