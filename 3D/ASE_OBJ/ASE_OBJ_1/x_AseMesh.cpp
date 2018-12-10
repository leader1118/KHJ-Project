#include "x_AseMesh.h"
void x_AseMesh::GetData(void* pData)
{
	_stscanf(m_pBuffer, _T("%s%f%f%f"),
		m_pString,
		&((D3DXVECTOR3*)pData)->x,
		&((D3DXVECTOR3*)pData)->z,
		&((D3DXVECTOR3*)pData)->y);


}
void x_AseMesh::LoadGeomObject() // 전부 쪼개서 함수로 만들어서 넣어버리는게 좋을꺼같음..
{
	xGeomMesh geomObject;
	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%s"), m_pString, m_pString2);
	geomObject.name = m_pString2;
	while (!feof(pStream))
	{
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);
		
		D3DXMatrixIdentity(&geomObject.matWorld);
		
		if (!_tcsicmp(m_pString, _T("*TM_ROWO")))
		{
			void* pVoidRow = geomObject.matWorld.m[0];
			//D3DXVECTOR3* pRow = (D3DXVECTOR3*)pVoidRow;
			GetData(&geomObject.matWorld.m[0]);
			_fgetts(m_pBuffer, 256, pStream);
			GetData(&geomObject.matWorld.m[2]);
			_fgetts(m_pBuffer, 256, pStream);
			GetData(&geomObject.matWorld.m[1]);
			_fgetts(m_pBuffer, 256, pStream);
			GetData(&geomObject.matWorld.m[3]);
			/*_stscanf(m_pBuffer, _T("%s%f%f%f"), 
				&((D3DXVECTOR3*)pVoidRow)->x,
				&((D3DXVECTOR3*)pVoidRow)->y,
				&((D3DXVECTOR3*)pVoidRow)->z);*/

			/*pRow = &geomObject.matWorld[2];
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s%f%f%f"),
				&pRow[0], &pRow[2], &pRow[1]);

			pRow = &geomObject.matWorld[1];
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s%f%f%f"),
				&pRow[0], &pRow[2], &pRow[1]);

			pRow = &geomObject.matWorld[3];
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s%f%f%f"),
				&pRow[0], &pRow[2], &pRow[1]);*/
			break;
		}
	}
	while (!feof(pStream))
	{
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);
		if (!_tcsicmp(m_pString, _T("*MESH")))
		{
			
		}
		int iNumVertex = 0;
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s%d"), m_pString,iNumVertex);
		int iNumFace = 0;
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s%d"), m_pString,iNumFace);
		
		int iTmp;
		D3DXVECTOR3 vPos;
		geomObject.vertexList.resize(iNumVertex);
		for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
		{
			
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s%d%f%f%f"), m_pString, &iTmp,
				&geomObject.vertexList[iVertex].x
				,&geomObject.vertexList[iVertex].z
				,&geomObject.vertexList[iVertex].y);
		}
		
		_fgetts(m_pBuffer, 256, pStream);
		geomObject.PosFaceList.resize(iNumFace);
		for (int iface = 0; iface < iNumFace; iface++)
		{
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s%s %s%d %s%d %s%d %s%d %s%d %s%d %s%d %s%d"),
				m_pString,
				m_pString, 
				m_pString, 
				&geomObject.PosFaceList[iface].i[0]
				,m_pString
				,&geomObject.PosFaceList[iface].i[2]
				,m_pString
				,&geomObject.PosFaceList[iface].i[1]
				,m_pString 
				,m_pString,&iTmp,
				m_pString, &iTmp,
				m_pString, &iTmp,
				m_pString, &iTmp,
				m_pString, &geomObject.PosFaceList[iface].iSubMtrl);
		}
		_fgetts(m_pBuffer, 256, pStream);
	}
	m_ObjectList.push_back(geomObject);
}
void x_AseMesh::LoadScene()
{
	_fgetts(m_pBuffer, 256, pStream);

	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString,&m_Scene.iFirstFrame);
	
	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iLastFrame);
	
	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iFrameSpeed);
	
	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &m_Scene.iTickPerFrame);
	
}
void x_AseMesh::LoadMaterial()
{
	int iCount = 0;
	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%d"),m_pString, &iCount);
	
	for (int iCnt = 0; iCnt < iCount; iCnt++)
	{
		
		while (!feof(pStream))
		{
			_fgetts(m_pBuffer, 256, pStream);
			_stscanf(m_pBuffer, _T("%s"), m_pString);
			if (!_tcsicmp(m_pString, _T("*MAP_SUBNO")))
			{
				break;
			}
		}
		
	}
	_stscanf(m_pBuffer, _T("%s%d"), m_pString, &tMap.iType);

	_fgetts(m_pBuffer, 256, pStream);

	_fgetts(m_pBuffer, 256, pStream);
	_stscanf(m_pBuffer, _T("%s%s"), m_pString, m_pString2);

	TCHAR Dirve[256] = { 0, };
	TCHAR Dir[256] = { 0, };
	TCHAR fname[256] = { 0, };
	TCHAR ext[256] = { 0, };
	_tsplitpath(m_pString2,Dirve,Dir,fname,ext);

	
	tMap.name = fname;
	ext[4] = 0;
	tMap.name += ext;
	xMat.m_mapList.push_back(tMap);
	m_MaterialList.push_back(xMat);
}
bool x_AseMesh::Load(T_STR name)
{
	pStream = NULL;
	pStream = _tfopen(name.c_str(), _T("rt"));
	if (pStream == NULL)
	{
		return false;
	}
	
	while (!feof(pStream))
	{
		_fgetts(m_pBuffer,256,pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);
		if (!_tcsicmp(m_pString, _T("*SCENE")))
		{
			LoadScene(); // 함수로 만들어 놓자!
			break;
		}
		
	}
	while (!feof(pStream))
	{
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);
		
		if (!_tcsicmp(m_pString, _T("*MATERIAL_LIST")))
		{
			LoadMaterial(); // 함수로 만들어 놓자!
			break;
		}
	}
	while (!feof(pStream))
	{
		_fgetts(m_pBuffer, 256, pStream);
		_stscanf(m_pBuffer, _T("%s"), m_pString);

		if (!_tcsicmp(m_pString, _T("*GEOMOBJECT")))
		{
			LoadGeomObject(); // 함수로 만들어 놓자!
			
		}
	}
	fclose(pStream);
	return true;
}


x_AseMesh::x_AseMesh()
{
}


x_AseMesh::~x_AseMesh()
{
}
